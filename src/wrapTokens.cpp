/*
Created by vfx at October 10/31/24 (18:18:09)

author        : Seongcheol Jeon
project       : FTH_AR
file path     : src/wrapTokens.cpp
created date  : 2024.10.31
modified date : 2024.10.31
description   : 
*/

//
// Created by vfx on 10/31/24.
//

#include "boostHeaderWrapper.h"

#include BOOST_INCLUDE(python/class.hpp)
#include "tokens.h"

PXR_NAMESPACE_USING_DIRECTIVE

namespace {
    class _WrapStaticToken {
    public:
        _WrapStaticToken(const TfToken *token) : _token(token) {}

        std::string operator()() const {
            return _token->GetString();
        }

    private:
        const TfToken *_token;
    };
}

template<typename T>
void
_AddToken(T &cls, const char *name, const TfToken &token) {
    cls.add_static_property(
            name,
            BOOST_NAMESPACE::python::make_function(
                    _WrapStaticToken(&token),
                    BOOST_NAMESPACE::python::return_value_policy<BOOST_NAMESPACE::python::return_by_value>(),
                    BOOST_NAMESPACE::mpl::vector1<std::string>()
            )
    );
}

void wrapFTHArResolverTokens(){
    BOOST_NAMESPACE::python::class_<FTHArResolverTokensType, BOOST_NAMESPACE::noncopyable>
            cls("Tokens", BOOST_NAMESPACE::python::no_init);
    _AddToken(cls, "replacePairs", FTHArResolverTokens->replacePairs);
    _AddToken(cls, "replaceFileName", FTHArResolverTokens->replaceFileName);
}