cmake_minimum_required(VERSION 3.28)
project(LayersSFML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Dependemcies
include(Dependencies.cmake)

# Compilation options
if(MSVC)
    add_compile_options(
        /W4
        /utf-8
    )
endif()

# Projects
add_subdirectory(Core)
add_subdirectory(App)

# StartUp Project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT App)
