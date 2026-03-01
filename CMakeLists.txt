cmake_minimum_required(VERSION 3.28)
project(LayersSFML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependemcies
include(Dependencies.cmake)

# Projects
add_subdirectory(Core)
add_subdirectory(App)

# StartUp Project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT App)
