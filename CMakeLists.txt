cmake_minimum_required(VERSION 3.28)
project(LayersSFML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
)

FetchContent_MakeAvailable(SFML)

add_executable(LayersSFML src/main.cpp src/Layer.cpp src/Application.cpp src/Window.cpp src/AppLayer.cpp)

target_link_libraries(LayersSFML PRIVATE sfml-graphics sfml-window sfml-system)

set_target_properties(LayersSFML PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LayersSFML)
