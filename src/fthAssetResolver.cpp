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

#include "fthAssetResolver.h"

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

#include <fmt/core.h>
#include <fmt/color.h>

#include <tbb/concurrent_hash_map.h>
#include <fstream>

#include <string>

PXR_NAMESPACE_OPEN_SCOPE

    AR_DEFINE_RESOLVER(FTHArResolver, ArResolver);

#define FTH_PREFIX      "FTHArResolver:"
#define FTH_PREFIX_LEN  14



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

PXR_NAMESPACE_CLOSE_SCOPE