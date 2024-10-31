/*
Created by vfx at October 10/31/24 (17:00:54)

author        : Seongcheol Jeon
project       : FTH_AR
file path     : src/debugCodes.cpp
created date  : 2024.10.31
modified date : 2024.10.31
description   : 
*/

//
// Created by vfx on 10/31/24.
//

#include "debugCodes.h"

#include <pxr/pxr.h>
#include <pxr/base/tf/debug.h>
#include <pxr/base/tf/registryManager.h>

PXR_NAMESPACE_OPEN_SCOPE

    TF_REGISTRY_FUNCTION(TfDebug)
    {
        TF_DEBUG_ENVIRONMENT_SYMBOL(REPLACERESOLVER_PATH, "Prints the path of the asset to be replaced.");
        TF_DEBUG_ENVIRONMENT_SYMBOL(REPLACERESOLVER_REPLACE, "Prints the path of the asset to be replaced with.");
        TF_DEBUG_ENVIRONMENT_SYMBOL(REPLACERESOLVER_CURRENTCONTEXT, "Prints the current context of the asset resolver.");
    }

PXR_NAMESPACE_CLOSE_SCOPE
