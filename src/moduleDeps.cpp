/*
Created by vfx at October 10/31/24 (17:10:04)

author        : Seongcheol Jeon
project       : FTH_AR
file path     : src/moduleDeps.cpp
created date  : 2024.10.31
modified date : 2024.10.31
description   : 
*/

//
// Created by vfx on 10/31/24.
//

#include <pxr/pxr.h>
#include <pxr/base/tf/registryManager.h>
#include <pxr/base/tf/scriptModuleLoader.h>
#include <pxr/base/tf/token.h>

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

    TF_REGISTRY_FUNCTION(TfScriptModuleLoader) {
        const std::vector<TfToken> reqs = {
                TfToken("ar"),
                TfToken("sdf")
        };
        TfScriptModuleLoader::GetInstance().RegisterLibrary(TfToken("FTHArResolver"), TfToken("fth.FTHArResolver"),
                                                            reqs);
    }

PXR_NAMESPACE_CLOSE_SCOPE