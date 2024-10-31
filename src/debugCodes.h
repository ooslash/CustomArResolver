/*
Created by vfx at October 10/31/24 (17:00:54)

author        : Seongcheol Jeon
project       : FTH_AR
file path     : src/debugCodes.h
created date  : 2024.10.31
modified date : 2024.10.31
description   : 
*/

//
// Created by vfx on 10/31/24.
//

#ifndef FTH_AR_DEBUGCODES_H
#define FTH_AR_DEBUGCODES_H

#include <pxr/pxr.h>
#include <pxr/base/tf/debug.h>

PXR_NAMESPACE_OPEN_SCOPE

    TF_DEBUG_CODES(
            REPLACERESOLVER_PATH,
            REPLACERESOLVER_REPLACE,
            REPLACERESOLVER_CURRENTCONTEXT
    );

PXR_NAMESPACE_CLOSE_SCOPE

#endif //FTH_AR_DEBUGCODES_H
