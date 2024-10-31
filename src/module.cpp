/*
Created by vfx at October 10/31/24 (17:05:38)

author        : Seongcheol Jeon
project       : FTH_AR
file path     : src/module.cpp
created date  : 2024.10.31
modified date : 2024.10.31
description   : 
*/

//
// Created by vfx on 10/31/24.
//

#include <pxr/pxr.h>
#include <pxr/base/tf/pyModule.h>

PXR_NAMESPACE_USING_DIRECTIVE

TF_WRAP_MODULE{
    TF_WRAP(FTHArResolver);
    TF_WRAP(FTHArResolverContext);
    TF_WRAP(FTHArResolverTokens);
};