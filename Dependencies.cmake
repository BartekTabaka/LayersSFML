#
# Dependencies
#

include(FetchContent)

# Do not build modules that are not used (reduces compilation time)
set(SFML_BUILD_AUDIO   OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

# SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.2
    GIT_SHALLOW    TRUE       # Downloads only the specified tag, not the entire history
    SYSTEM                    # SFML warnings won't clutter your build (CMake >= 3.25)
    FIND_PACKAGE_ARGS 3.0.2   # First looks for an installed version on the system (CMake >= 3.24)
)

FetchContent_MakeAvailable(SFML)