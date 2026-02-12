cmake_minimum_required(VERSION 3.28)
project(LayersSFML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
)

FetchContent_MakeAvailable(SFML)

add_executable(LayersSFML src/main.cpp)

target_link_libraries(LayersSFML PRIVATE sfml-graphics sfml-window sfml-system)
