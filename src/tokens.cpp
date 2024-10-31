/*
Created by vfx at October 10/31/24 (17:15:10)

author        : Seongcheol Jeon
project       : FTH_AR
file path     : src/tokens.cpp
created date  : 2024.10.31
modified date : 2024.10.31
description   : 
*/

//
// Created by vfx on 10/31/24.
//

#include "tokens.h"

PXR_NAMESPACE_OPEN_SCOPE

    FTHArResolverTokensType::FTHArResolverTokensType()
            : replacePairs("replacePairs", TfToken::Immortal),
              replaceFileName("replace.json", TfToken::Immortal),
              allTokens({replacePairs}) {}

    TfStaticData<FTHArResolverTokensType> FTHArResolverTokens;

PXR_NAMESPACE_CLOSE_SCOPE
