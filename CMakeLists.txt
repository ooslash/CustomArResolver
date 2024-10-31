cmake_minimum_required(VERSION 3.29)
project(FTH_AR)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
list(APPEND CMAKE_PREFIX_PATH "/home/vfx/packages_cache/houdini/20.0.688/5c54/a/toolkit/cmake")

#find_package(USD REQUIRED)
find_package(fmt REQUIRED)
find_package(Houdini REQUIRED)

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

set(USD_PLUGIN_NAME "FTHArResolver")

add_subdirectory(src)

install(
        DIRECTORY etc
        DESTINATION .
)