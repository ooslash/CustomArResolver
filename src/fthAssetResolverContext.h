/*
Created by vfx at October 10/31/24 (12:09:40)

author        : Seongcheol Jeon
project       : FTH_AR
file path     : src/fthAssetResolverContext.h
created date  : 2024.10.31
modified date : 2024.10.31
description   : 
*/

//
// Created by vfx on 10/31/24.
//

#ifndef FTH_AR_FTHASSETRESOLVERCONTEXT_H
#define FTH_AR_FTHASSETRESOLVERCONTEXT_H


#include <pxr/pxr.h>
#include <pxr/usd/ar/api.h>
#include <pxr/usd/ar/defineResolverContext.h>

#include <string>
#include <vector>
#include <map>


PXR_NAMESPACE_OPEN_SCOPE

    class FTHArResolverContext {
    public:
        FTHArResolverContext() = default;

        AR_API
        FTHArResolverContext(const std::vector<std::string> &searchPath);

        AR_API
        void AddReplacePair(const std::string &oldStr, const std::string &newStr);

        const std::map<std::string, std::string> &GetReplaceMap() const {
            return _oldAndNewStrings;
        }

        AR_API
        bool operator<(const FTHArResolverContext &ref) const;

        AR_API
        bool operator==(const FTHArResolverContext &ref) const;

        AR_API
        bool operator!=(const FTHArResolverContext &ref) const;

        const std::vector<std::string> &GetSearchPath() const {
            return _searchPath;
        }

        AR_API
        std::string GetAsString() const;

    private:
        std::vector<std::string> _searchPath;
        std::map<std::string, std::string> _oldAndNewStrings;
    };

    AR_API
    size_t hash_value(const FTHArResolverContext &context);

    inline std::string ArGetDebugString(const FTHArResolverContext &context) {
        return context.GetAsString();
    }

    AR_DECLARE_RESOLVER_CONTEXT(FTHArResolverContext);

PXR_NAMESPACE_CLOSE_SCOPE


#endif //FTH_AR_FTHASSETRESOLVERCONTEXT_H
