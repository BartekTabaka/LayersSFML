#
# Core
#

# Files
set(CORE_SOURCES
    Source/Core/Application.h
    Source/Core/Application.cpp
    Source/Core/Window.h
    Source/Core/Window.cpp
    Source/Core/Layer.h
    Source/Core/Layer.cpp
    Source/Core/Event.h
    Source/Core/InputEvents.h

    Source/Core/Asset/AssetIDs.h
    Source/Core/Asset/AssetLoader.h
    Source/Core/Asset/AssetLoadError.h
    Source/Core/Asset/AssetContainer.h
    Source/Core/Asset/AssetManager.h
    Source/Core/Asset/AssetManager.cpp
)

# Library definition    
add_library(Core STATIC)

# Set sources
target_sources(Core PRIVATE ${CORE_SOURCES})
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

#Match VS filters to directory structure on disk
#source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${CORE_SOURCES})

target_link_libraries(Core
    PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)
