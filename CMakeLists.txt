cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
project(FTH_AR VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
if (WIN32)
    list(APPEND CMAKE_PREFIX_PATH "C:/Program Files/Side Effects Software/Houdini 20.5.370/toolkit/cmake")
    set(FMT_LOCATION "C:/developments/OpenUSD/lib/cmake/fmt")
    set(SPDLOG_LOCATION "C:/developments/OpenUSD/lib64/cmake/spdlog")
    set(_PYTHON_VERSION "3.11")
else ()
    list(APPEND CMAKE_PREFIX_PATH "/home/vfx/packages_cache/houdini/20.0.688/5c54/a/toolkit/cmake")
    set(FMT_LOCATION "/home/vfx/development/library/lib64/cmake/fmt")
    set(SPDLOG_LOCATION "/home/vfx/development/library/lib64/cmake/spdlog")
    set(_PYTHON_VERSION "3.10")
endif ()

include(handleBoostNamespace)

#find_package(USD REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(Houdini REQUIRED)

#set(Python3_ROOT_DIR "C:/Program Files/Side Effects Software/Houdini 20.5.370/python311")
#find_package(Python3 REQUIRED COMPONENTS Development)

#######################################################################
if (NOT Houdini_FOUND)
    message(FATAL_ERROR "Houdini not found")
else ()
    message(STATUS "Houdini found")
    message(STATUS "Houdini version: ${Houdini_VERSION}")
    message(STATUS "Houdini Install Root: ${_houdini_install_root}")
    message(STATUS "Houdini Include Dir: ${_houdini_include_dir}")
endif ()
#######################################################################

if (LINUX)
    set(DSO_EXT "so")
elseif (APPLE)
    set(DSO_EXT "dylib")
else ()
    set(DSO_EXT "dll")
endif ()

set(USD_PLUGIN_NAME "FTHArResolver")

set(EXTERNAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)

set(Z85_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/external/z85/z85_impl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/external/z85/z85.c
)

# install...
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

add_subdirectory(src)

install(
        DIRECTORY etc
        DESTINATION .
)