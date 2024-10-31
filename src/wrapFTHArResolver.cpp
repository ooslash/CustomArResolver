/*
Created by vfx at October 10/31/24 (17:27:29)

author        : Seongcheol Jeon
project       : FTH_AR
file path     : src/wrapFTHArResolver.cpp
created date  : 2024.10.31
modified date : 2024.10.31
description   : 
*/

//
// Created by vfx on 10/31/24.
//

#include "fthAssetResolver.h"

#include "boostHeaderWrapper.h"

#include <pxr/pxr.h>

#include BOOST_INCLUDE(python/class.hpp)

using namespace BOOST_NAMESPACE::python;

PXR_NAMESPACE_USING_DIRECTIVE

void
wrapFTHArResolver(){
    using This = FTHArResolver;

    class_<This, bases<ArResolver>, BOOST_NAMESPACE::noncopyable>
            ("FTHArResolver", no_init)
            .def("SetDefaultSearchPath", &This::SetDefaultSearchPath, args("searchPath"))
            .staticmethod("SetDefaultSearchPath");
}
