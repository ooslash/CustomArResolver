/*
Created by vfx at October 10/31/24 (17:35:10)

author        : Seongcheol Jeon
project       : FTH_AR
file path     : src/wrapFTHArResolverContext.cpp
created date  : 2024.10.31
modified date : 2024.10.31
description   : 
*/

//
// Created by vfx on 10/31/24.
//

#include "fthAssetResolverContext.h"

#include "boostHeaderWrapper.h"

#include BOOST_INCLUDE(python/class.hpp)
#include BOOST_INCLUDE(python/operators.hpp)
#include BOOST_INCLUDE(python/return_by_value.hpp)
#include BOOST_INCLUDE(python/return_value_policy.hpp)

#include <pxr/pxr.h>
#include <pxr/usd/ar/pyResolverContext.h>
#include <pxr/base/tf/pyUtils.h>

using namespace BOOST_NAMESPACE::python;

PXR_NAMESPACE_USING_DIRECTIVE

static std::string
_Repr(const FTHArResolverContext &ctx) {
    std::string repr = TF_PY_REPR_PREFIX;
    repr += "FTHArResolverContext(";
    repr += ctx.GetAsString();
    repr += ")";
    return repr;
}

static size_t
_Hash(const FTHArResolverContext &ctx) {
    return hash_value(ctx);
}

void
wrapFTHArResolverContext() {
    using This = FTHArResolverContext;

    class_<This>
            ("FTHArResolverContext", no_init)
            .def(init<>())
            .def(init<const std::vector<std::string> &>(
                    arg("searchPaths")))
            .def(self == self)
            .def(self != self)
            .def("GetSearchPath", &This::GetSearchPath, return_value_policy<return_by_value>())
            .def("__str__", &This::GetAsString)
            .def("__repr__", &_Repr)
            .def("__hash__", &_Hash);

    ArWrapResolverContextForPython<This>();
}


