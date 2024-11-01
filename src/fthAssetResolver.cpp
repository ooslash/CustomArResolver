/*
Created by vfx at October 10/30/24 (17:25:30)

author        : Seongcheol Jeon
project       : FTH_AR
file path     : src/fthAssetResolver.cpp
created date  : 2024.10.30
modified date : 2024.10.30
description   : 
*/

//
// Created by vfx on 10/30/24.
//

#include "debugCodes.h"
#include "fthAssetResolver.h"
#include "fthAssetResolverContext.h"
#include "tokens.h"

#include <pxr/base/arch/fileSystem.h>
#include <pxr/base/arch/systemInfo.h>
#include <pxr/base/js/json.h>
#include <pxr/base/tf/fileUtils.h>
#include <pxr/base/tf/getenv.h>
#include <pxr/base/tf/pathUtils.h>
#include <pxr/base/tf/staticData.h>
#include <pxr/base/tf/stringUtils.h>
#include <pxr/base/tf/diagnostic.h>
#include <pxr/base/vt/value.h>
#include <pxr/usd/ar/defaultResolver.h>
#include <pxr/usd/ar/assetInfo.h>
#include <pxr/usd/ar/defineResolver.h>
#include <pxr/usd/ar/filesystemAsset.h>
#include <pxr/usd/ar/filesystemWritableAsset.h>
#include <pxr/usd/ar/resolverContext.h>
#include <pxr/usd/sdf/layer.h>
#include <pxr/usd/sdf/path.h>

#include <fmt/core.h>
#include <fmt/color.h>
#include <spdlog/spdlog.h>

#include <tbb/concurrent_hash_map.h>
#include <fstream>

#include <string>

PXR_NAMESPACE_OPEN_SCOPE

    AR_DEFINE_RESOLVER(FTHArResolver, ArResolver);

#define FTH_PREFIX      "FTHArResolver:"
#define FTH_PREFIX_LEN  14

    TfStaticData<std::vector<std::string>> _SearchPath;

    bool _GetReplacePairsFromUsdFile(const std::string &filePath, FTHArResolverContext &context) {
        bool found = false;
        auto layer = SdfLayer::FindOrOpen(TfAbsPath(filePath));
        if (layer) {
            auto layerMetaData = layer->GetMetadata();
            auto replaceData = layerMetaData->Get(SdfPath::AbsoluteRootPath(), SdfFieldKeys->CustomLayerData);

            if (!replaceData.IsEmpty()) {
                TF_DEBUG(REPLACERESOLVER_REPLACE).Msg("Replace metadata found in file: \"%s\"\n", filePath.c_str());

                VtDictionary dic = replaceData.Get<VtDictionary>();
                auto it = dic.find(FTHArResolverTokens->replacePairs);
                if (it != dic.end()) {
                    VtValue allPairsValue = dic[FTHArResolverTokens->replacePairs];
                    VtStringArray allPairs = allPairsValue.Get<VtStringArray>();
                    if (allPairs.size() > 0) {
                        found = true;
                        for (size_t i = 0; i < allPairs.size(); i += 2) {
                            context.AddReplacePair(allPairs[i], allPairs[i + 1]);
                        }
                    }
                }
            }
        }
        return found;
    }

    bool _GetReplacePairsFromJsonFile(const std::string &filePath, FTHArResolverContext &context) {
        bool found = false;

        std::string assetDir = TfGetPathName(TfAbsPath(filePath));
        std::string replaceFilePath = TfNormPath(TfStringCatPaths(assetDir, FTHArResolverTokens->replaceFileName));

        std::ifstream ifs(replaceFilePath);

        if (ifs) {
            TF_DEBUG(REPLACERESOLVER_REPLACE).Msg("Replace file found: \"%s\"\n", replaceFilePath.c_str());

            JsParseError error;
            const JsValue value = JsParseStream(ifs, &error);
            ifs.close();

            if (!value.IsNull() && value.IsArray()) {
                if (value.GetJsArray().size() > 0) {
                    found = true;
                    for (const auto &pair: value.GetJsArray()) {
                        if (pair.IsArray()) {
                            context.AddReplacePair(pair.GetJsArray()[0].GetString(), pair.GetJsArray()[1].GetString());
                        }
                    }
                }
            } else {
                fprintf(stderr, "Error: parse error at %s:%d:%d: %s\n", replaceFilePath.c_str(), error.line,
                        error.column, error.reason.c_str());
            }
        }
        return found;
    }

    std::string FTHArResolver::ResolveWithAssetInfo(const std::string &assetPath, ArAssetInfo *assetInfo){
        TF_DEBUG(REPLACERESOLVER_PATH).Msg("Unresolved Path: \"%s\"\n", assetPath.c_str());
        if(assetPath.empty()){
            return assetPath;
        }
        std::string resolvedPath;
        if(_CachePtr currentCache = _GetCurrentCache()){
            asdf
        }
    }

    std::string FTHArResolver::_ResolveNoCache(const std::string& path) {
        SdfPath _sdfPath = SdfPath(path);
        if (_sdfPath.IsEmpty()) {
            return path;
        }

        if(!_sdfPath.IsAbsolutePath()) {
            std::string resolvedPath = _Resolve(ArchGetCwd(), path);
            if (!resolvedPath.empty()) {
                return resolvedPath;
            }

            // Check if path is a search path, replacing IsSearchPath functionality
            auto currentContext = _GetCurrentContext();
            const ReplaceResolverContext* contexts[] = {currentContext, &_fallbackContext};

            if (currentContext) {
                TF_DEBUG(REPLACERESOLVER_CURRENTCONTEXT).Msg(
                            "ReplaceResolverContext: \"%s\"\n",
                            ArResolverContext(*currentContext).GetDebugString().c_str());
            }

            for (const auto* ctx : contexts) {
                if (ctx) {
                    // Apply context-based replacements to the path
                    std::string replacedPath = _ReplaceFromContext(*ctx, path);

                    // Attempt to resolve path against each search directory
                    for (const auto& searchPath : ctx->GetSearchPath()) {
                        resolvedPath = _Resolve(searchPath, replacedPath);
                        if (!resolvedPath.empty()) {
                            return resolvedPath;
                        }
                    }
                }
            }

            return {};
        }

        // Absolute path resolution
        return _Resolve({}, path);
    }

    bool _IsFileRelative(const std::string &path) {
        return path.find("./") == 0 || path.find("../") == 0;
    }

    void FTHArResolver::ConfigureResolverForAsset(const std::string &path) {
        this->_defaultContext = CreateDefaultContextForAsset(path);
    }

    std::vector<std::string> _GetSearchPaths() {
        std::vector<std::string> searchPath = *_SearchPath;

        const std::string envPath = TfGetenv("PXR_AR_DEFAULT_SEARCH_PATH");
        if (!envPath.empty()) {
            const std::vector<std::string> envSearchPath = TfStringTokenize(envPath, ARCH_PATH_LIST_SEP);
            searchPath.insert(searchPath.end(), envSearchPath.begin(), envSearchPath.end());
        }

        return searchPath;
    }

    ArResolverContext FTHArResolver::CreateDefaultContextForAsset(const std::string &filePath) {
        if (filePath.empty()) {
            return ArResolverContext(FTHArResolverContext());
        }
        auto context = FTHArResolverContext(_GetSearchPaths());

        std::string extension = TfGetExtension(filePath);
        if (extension == "usd" || extension == "usda" || extension == "usdc") {
            _GetReplacePairsFromUsdFile(filePath, context);
        }

        _GetReplacePairsFromJsonFile(filePath, context);

        return ArResolverContext(context);
    }

    std::string
    FTHArResolver::_CreateIdentifier(const std::string &assetPath, const ArResolvedPath &anchorAssetPath) const {
        if (assetPath.empty()) {
            return assetPath;
        }
        if (!anchorAssetPath) {
            return TfNormPath(assetPath);
        }

        if (assetPath.length() > FTH_PREFIX_LEN && assetPath.substr(0, FTH_PREFIX_LEN).compare(FTH_PREFIX) == 0) {
            return assetPath;
        }

        return TfStringCatPaths(anchorAssetPath, assetPath);
    }

    std::string FTHArResolver::_CreateIdentifierForNewAsset(const std::string &assetPath,
                                                            const ArResolvedPath &anchorAssetPath) const {
        return _CreateIdentifier(assetPath, anchorAssetPath);
    }

    ArResolvedPath
    FTHArResolver::_Resolve(const std::string &assetPath) const {
        ArResolvedPath newPath = _ResolveForNewAsset(assetPath);

        if (assetPath == (std::string(FTH_PREFIX) + "foo")) {
            return ArResolvedPath("bar");
        }

        fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
                   "[[Callback]] _Resolve: {}", newPath.GetPathString());

        return TfPathExists(newPath) ? newPath : ArResolvedPath();
    }

    ArResolvedPath FTHArResolver::_ResolveForNewAsset(const std::string &assetPath) const {
        if (assetPath.empty()) {
            return ArResolvedPath();
        }

        static const std::string theTempDir(TfGetenv("HOME"));

        std::string newPath = TfStringCatPaths(theTempDir, assetPath.substr(FTH_PREFIX_LEN));

        return ArResolvedPath(newPath);
    }

    std::shared_ptr<ArAsset> FTHArResolver::_OpenAsset(const ArResolvedPath &resolvedPath) const {
        return ArFilesystemAsset::Open(resolvedPath);
    }

    std::shared_ptr<ArWritableAsset>
    FTHArResolver::_OpenAssetForWrite(const ArResolvedPath &resolvedPath, ArResolver::WriteMode writeMode) const {
        return ArFilesystemWritableAsset::Create(_ResolveForNewAsset(resolvedPath), writeMode);
    }

    void FTHArResolver::SetDefaultSearchPath(const std::vector<std::string> &searchPath) {
        *_SearchPath = searchPath;
    }

PXR_NAMESPACE_CLOSE_SCOPE