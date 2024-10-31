# Created by vfx at October 10/30/24 (17:21:04)

# author        : Seongcheol Jeon
# project       : FTH_AR
# file path     : src/handleBoostNamespace.cmake
# created date  : 2024.10.30
# modified date : 2024.10.30
# description   :

add_library(${USD_PLUGIN_NAME}
        SHARED
        fthAssetResolver.h
        fthAssetResolver.cpp
        boostHeaderWrapper.h
        fthAssetResolverContext.h
        fthAssetResolverContext.cpp
        debugCodes.cpp
        debugCodes.h
        tokens.cpp
        tokens.h
)

set_boost_namespace(${USD_PLUGIN_NAME})

#target_include_directories(${USD_PLUGIN_NAME}
#        PRIVATE
#        ${PXR_INCLUDE_DIRS}
#)

#target_link_libraries(${USD_PLUGIN_NAME}
#        ar
#        sdf
#        fmt::fmt
#)

target_link_libraries(${USD_PLUGIN_NAME}
        Houdini
        fmt::fmt
)

target_include_directories(${USD_PLUGIN_NAME}
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

set_target_properties(${USD_PLUGIN_NAME} PROPERTIES PREFIX "")

#target_compile_features(${USD_PLUGIN_NAME}
#        PUBLIC
#        cxx_auto_type
#        cxx_lambdas
#        cxx_nullptr
#        cxx_range_for
#)

set(libraryName ${USD_PLUGIN_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX})

configure_file(
        plugInfo.json.in
#        ${CMAKE_BINARY_DIR}/plugInfo.json
        ${CMAKE_INSTALL_PREFIX}/plugInfo.json
        @ONLY
)

# install library
install(
        TARGETS ${USD_PLUGIN_NAME}
        LIBRARY DESTINATION plugin/usd
)

# install plugInfo
install(
        FILES ${CMAKE_BINARY_DIR}/plugInfo.json
        DESTINATION plugin/usd/${USD_PLUGIN_NAME}/resources
)

if (NOT EXISTS ${CMAKE_INSTALL_PREFIX}/plugin/usd/plugInfo.json)
    configure_file(
#            ${USD_PLUGINS_DIR}/plugInfo.json
            ${CMAKE_INSTALL_PREFIX}/plugInfo.json
            ${CMAKE_INSTALL_PREFIX}/plugin/usd/plugInfo.json
            COPYONLY
    )
endif ()

# Python Bindings
set(PXR_ENABLE_PYTHON_SUPPORT ON)
if (PXR_ENABLE_PYTHON_SUPPORT)
    set(USD_PLUGIN_PYTHON_NAME _${USD_PLUGIN_NAME})

    string(REPLACE "_" "" LIBNAME "${USD_PLUGIN_PYTHON_NAME}")
    string(SUBSTRING "${LIBNAME}" 0 1 LIBNAME_FIRST_CHAR)
    string(TOUPPER "${LIBNAME_FIRST_CHAR}" LIBNAME_FIRST_CHAR)
    string(SUBSTRING "${LIBNAME}" 1 -1 LIBNAME_SUFFIX)
    set(MODULE_NAME "${LIBNAME_FIRST_CHAR}${LIBNAME_SUFFIX}")

    add_library(${USD_PLUGIN_PYTHON_NAME}
            SHARED
            boostHeaderWrapper.h
            module.cpp
            moduleDeps.cpp
            wrapFTHArResolver.cpp
            wrapFTHArResolverContext.cpp
            wrapTokens.cpp
    )

    set_boost_namespace(${USD_PLUGIN_PYTHON_NAME})

    set_target_properties(${USD_PLUGIN_PYTHON_NAME}
            PROPERTIES
            INSTALL_RPATH "$ORIGIN/../../../../../plugin/usd"
    )

    target_include_directories(${USD_PLUGIN_PYTHON_NAME}
            PRIVATE
            # TODO: 이거 아마...
            ${PXR_INCLUDE_DIRS}
    )

    set_target_properties(${USD_PLUGIN_PYTHON_NAME} PROPERTIES SUFFIX ".so")

    set_target_properties(${USD_PLUGIN_PYTHON_NAME}
            PROPERTIES
            PREFIX ""
    )

    target_compile_definitions(${USD_PLUGIN_PYTHON_NAME}
            PRIVATE
            MFB_PACKAGE_NAME=${USD_PLUGIN_NAME}
            MFB_ALT_PACKAGE_NAME=${USD_PLUGIN_NAME}
            MFB_PACKAGE_MODULE=fth.${MODULE_NAME}
    )

    target_link_libraries(${USD_PLUGIN_PYTHON_NAME}
            ${USD_PLUGIN_NAME}
    )

    # ${_houdini_python_version} -> 3.10
    set(PYTHON_PACKAGE_RELATIVE_PATH "lib/python${_houdini_python_version}/site-packages/fth")
    set(INSTALL_PYTHON_PACKAGE_DIR "${CMAKE_INSTALL_PREFIX}/${PYTHON_PACKAGE_RELATIVE_PATH}")
    set(INSTALL_WRAPPER_DIR "${INSTALL_PYTHON_PACKAGE_DIR}/${MODULE_NAME}")

    install(
            TARGETS ${USD_PLUGIN_PYTHON_NAME}
            DESTINATION ${INSTALL_WRAPPER_DIR}
    )

    file(WRITE ${INSTALL_PYTHON_PACKAGE_DIR}/__init__.py "''' fth(4th) Asset Resolver Python Bindings '''")

    install(
            FILES __init__.py
            DESTINATION ${INSTALL_WRAPPER_DIR}
    )

endif ()
