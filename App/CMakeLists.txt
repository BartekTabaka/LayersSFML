#
# App
#

# Files
set(APP_SOURCES
    Source/Main.cpp

    Source/AppLayer.h
    Source/AppLayer.cpp
    Source/OverlayLayer.h
    Source/OverlayLayer.cpp
    Source/VoidLayer.h
    Source/VoidLayer.cpp
    Source/Rendering/RenderObject.h
)

# Add executable (.exe)
add_executable(App)

target_sources(App PRIVATE ${APP_SOURCES})
target_include_directories(App PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)

# Link libraries
target_link_libraries(App PRIVATE Core)

# Windows-only stuff
if (WIN32)
    set_target_properties(App PROPERTIES 
        WIN32_EXECUTABLE $<CONFIG:RELEASE>
    )
endif()

# Working directory
set_target_properties(App PROPERTIES 
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/App"
)
