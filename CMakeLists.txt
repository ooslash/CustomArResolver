cmake_minimum_required(VERSION 3.29)
project(FTH_AR)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

find_package(USD REQUIRED)
find_package(fmt REQUIRED)

set(USD_PLUGIN_NAME "FTHArResolver")

add_subdirectory(src)

install(
        DIRECTORY etc
        DESTINATION .
)