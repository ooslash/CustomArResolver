/*
Created by vfx at October 10/31/24 (17:15:10)

author        : Seongcheol Jeon
project       : FTH_AR
file path     : src/tokens.h
created date  : 2024.10.31
modified date : 2024.10.31
description   : 
*/

//
// Created by vfx on 10/31/24.
//

#ifndef FTH_AR_TOKENS_H
#define FTH_AR_TOKENS_H

#include <pxr/base/tf/staticTokens.h>
#include <pxr/pxr.h>
#include <pxr/usd/ar/api.h>

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

struct FTHArResolverTokensType {
    AR_API
    FTHArResolverTokensType();

    const TfToken replacePairs;
    const TfToken replaceFileName;
    const std::vector<TfToken> allTokens;
};

extern AR_API TfStaticData<FTHArResolverTokensType> FTHArResolverTokens;

PXR_NAMESPACE_CLOSE_SCOPE

#endif //FTH_AR_TOKENS_H
