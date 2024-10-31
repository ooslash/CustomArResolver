/*
Created by vfx at October 10/31/24 (12:09:40)

author        : Seongcheol Jeon
project       : FTH_AR
file path     : src/fthAssetResolverContext.cpp
created date  : 2024.10.31
modified date : 2024.10.31
description   : 
*/

//
// Created by vfx on 10/31/24.
//

#include <pxr/pxr.h>
#include <pxr/base/tf/diagnostic.h>
#include <pxr/base/tf/hash.h>
#include <pxr/base/tf/ostreamMethods.h>
#include <pxr/base/tf/pathUtils.h>
#include <pxr/base/tf/stringUtils.h>

#include "fthAssetResolverContext.h"

#include "boostHeaderWrapper.h"

#include BOOST_INCLUDE(functional / hash.hpp)

PXR_NAMESPACE_OPEN_SCOPE

    FTHArResolverContext::FTHArResolverContext(const std::vector<std::string> &searchPath) {
        _searchPath.reserve(searchPath.size());
        for (const std::string &p: searchPath) {
            if (p.empty()) {
                continue;
            }

            const std::string absPath = TfAbsPath(p);
            if (absPath.empty()) {
                TF_WARN("Could not determine absolute path for search path prefix "
                        "'%s'", p.c_str());
                continue;
            }

            _searchPath.push_back(absPath);
        }
    }

    void
    FTHArResolverContext::AddReplacePair(const std::string &oldStr, const std::string &newStr) {
        _oldAndNewStrings.emplace(std::piecewise_construct,
                                  std::forward_as_tuple(oldStr),
                                  std::forward_as_tuple(newStr));
    }

    bool
    FTHArResolverContext::operator<(const FTHArResolverContext &ref) const {
        bool result = _searchPath < ref._searchPath;
        if (result) {
            result = _oldAndNewStrings.size() < ref._oldAndNewStrings.size();
        }
        return result;
    }

    bool
    FTHArResolverContext::operator==(const FTHArResolverContext &ref) const {
        bool result = _searchPath == ref._searchPath;
        if (result) {
            result = _oldAndNewStrings.size() == ref._oldAndNewStrings.size();
        }
        return result;
    }

    bool
    FTHArResolverContext::operator!=(const FTHArResolverContext &ref) const {
        return !(*this == ref);
    }

    std::string
    FTHArResolverContext::GetAsString() const {
        std::string result = "Search Path: ";
        if (_searchPath.empty()) {
            result += "[ ]";
        } else {
            result += "[\n    ";
            result += TfStringJoin(_searchPath, "\n    ");
            result += "\n]";
        }

        if (_oldAndNewStrings.size() > 0) {
            result += "\nOld to New Token: ";
            result += "[";
            for (auto it = _oldAndNewStrings.begin(); it != _oldAndNewStrings.end(); it++) {
                result += "\n    " + it->first + ": ";
                result += it->second;
            }
            result += "\n]";
        }
        return result;
    }

    size_t
    hash_value(const FTHArResolverContext &context) {
        size_t hash = 0;
        for (const std::string &p: context.GetSearchPath()) {
            BOOST_NAMESPACE::hash_combine(hash, TfHash()(p));
        }

        auto replaceMap = context.GetReplaceMap();
        for (auto it = replaceMap.begin(); it != replaceMap.end(); it++) {
            BOOST_NAMESPACE::hash_combine(hash, TfHash()(it->first));
            BOOST_NAMESPACE::hash_combine(hash, TfHash()(it->second));
        }
        return hash;
    }

PXR_NAMESPACE_CLOSE_SCOPE

