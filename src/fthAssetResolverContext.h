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
};

PXR_NAMESPACE_CLOSE_SCOPE


#endif //FTH_AR_FTHASSETRESOLVERCONTEXT_H
