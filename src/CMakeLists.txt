# Created by vfx at October 10/30/24 (17:21:04)

# author        : Seongcheol Jeon
# project       : FTH_AR
# file path     : src/CMakeLists.txt
# created date  : 2024.10.30
# modified date : 2024.10.30
# description   :

add_library(${USD_PLUGIN_NAME}
        SHARED
        fthAssetResolver.h
        fthAssetResolver.cpp
        fthAssetResolverContext.cpp
        fthAssetResolverContext.h
)

target_include_directories(${USD_PLUGIN_NAME}
        PRIVATE
        ${PXR_INCLUDE_DIRS}
)

target_link_libraries(${USD_PLUGIN_NAME}
        ar
        sdf
        fmt::fmt
)

set_target_properties(${USD_PLUGIN_NAME} PROPERTIES PREFIX "")

target_compile_features(${USD_PLUGIN_NAME}
        PUBLIC
        cxx_auto_type
        cxx_lambdas
        cxx_nullptr
        cxx_range_for
)

set(libraryName ${USD_PLUGIN_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX})

configure_file(
        plugInfo.json.in
        ${CMAKE_BINARY_DIR}/plugInfo.json
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

if(NOT EXISTS ${CMAKE_INSTALL_PREFIX}/plugin/usd/plugInfo.json)
    configure_file(
            ${USD_PLUGINS_DIR}/plugInfo.json
            ${CMAKE_INSTALL_PREFIX}/plugin/usd/plugInfo.json
            COPYONLY
    )
endif()

#if(PXR_ENABLE_PYTHON_SUPPORT)
