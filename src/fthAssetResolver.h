/*
Created by vfx at October 10/30/24 (17:25:30)

author        : Seongcheol Jeon
project       : FTH_AR
file path     : src/fthAssetResolver.h
created date  : 2024.10.30
modified date : 2024.10.30
description   : 
*/

//
// Created by vfx on 10/30/24.
//

#ifndef FTH_AR_FTHASSETRESOLVER_H
#define FTH_AR_FTHASSETRESOLVER_H

#include <pxr/pxr.h>
#include <pxr/usd/ar/api.h>
#include <pxr/usd/ar/resolver.h>
#include <pxr/usd/ar/threadLocalScopedCache.h>
#include <pxr/base/vt/value.h>

#include <tbb/enumerable_thread_specific.h>

#include <memory>
#include <string>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

    class FTHArResolver final : public ArResolver {
    public:
        AR_API
        FTHArResolver() = default;

        AR_API
        ~FTHArResolver() override = default;

        AR_API
        static void SetDefaultSearchPath(const std::vector<std::string> &searchPath);

    protected:
        AR_API
        std::string
        _CreateIdentifier(const std::string &assetPath, const ArResolvedPath &anchorAssetPath) const override;

        AR_API
        std::string _CreateIdentifierForNewAsset(const std::string &assetPath,
                                                 const ArResolvedPath &anchorAssetPath) const override;

        AR_API
        ArResolvedPath _Resolve(const std::string &assetPath) const override;

        AR_API
        ArResolvedPath _ResolveForNewAsset(const std::string &assetPath) const override;

        AR_API
        std::shared_ptr<ArAsset> _OpenAsset(const ArResolvedPath &resolvedPath) const override;

        AR_API
        std::shared_ptr<ArWritableAsset>
        _OpenAssetForWrite(const ArResolvedPath &resolvedPath, WriteMode writeMode) const override;
    };

PXR_NAMESPACE_CLOSE_SCOPE

#endif //FTH_AR_FTHASSETRESOLVER_H
