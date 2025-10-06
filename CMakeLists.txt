cmake_minimum_required(VERSION 3.28)
project(AURELION)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(AURELION_WITH_RENDERING "Enable rendering dependencies (GLFW + GLAD)" ON)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ---- Rendering dependencies (optional) ----
if(AURELION_WITH_RENDERING)
    # GLFW
    # Reduce configure/build time by disabling extras
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG 3.3.9
    )
    FetchContent_MakeAvailable(glfw)

    # GLAD (OpenGL 3.3 core, C generator)
    set(GLAD_PROFILE "core" CACHE STRING "" FORCE)
    set(GLAD_API "gl=3.3" CACHE STRING "" FORCE)
    set(GLAD_GENERATOR "c" CACHE STRING "" FORCE)
    # Newer CMake requires policy minimum; set for subprojects like glad
    set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)
    FetchContent_Declare(
            glad
            GIT_REPOSITORY https://github.com/Dav1dde/glad.git
            GIT_TAG v0.1.36
    )
    FetchContent_MakeAvailable(glad)
endif()

enable_testing()

# --- Math library ---
add_library(math STATIC
        src/math/Vector3.cpp
)
# Export public headers under src/math so includes use "include/Vector3.h"
target_include_directories(math PUBLIC src/math)

# --- Math tests ---
add_executable(math_tests
        tests/tVector3.cpp
)
target_link_libraries(math_tests PRIVATE math gtest_main)
include(GoogleTest)
gtest_discover_tests(math_tests)

# --- Rendering smoke tests ---
if(AURELION_WITH_RENDERING)
    add_executable(render_smoke_tests
            tests/tRenderingSetup.cpp
    )
    if(WIN32)
        target_link_libraries(render_smoke_tests PRIVATE glfw glad gtest_main opengl32)
    else()
        target_link_libraries(render_smoke_tests PRIVATE glfw glad gtest_main)
    endif()
    # Ensure GLAD headers are generated before compiling this test
    if(TARGET glad-generate-files)
        add_dependencies(render_smoke_tests glad-generate-files)
    endif()
    gtest_discover_tests(render_smoke_tests)
endif()

# --- Main executable ---
add_executable(AURELION src/main.cpp)
# Always link math; link rendering deps only when enabled
if(AURELION_WITH_RENDERING)
    if(WIN32)
        target_link_libraries(AURELION PRIVATE math glfw glad opengl32)
    else()
        target_link_libraries(AURELION PRIVATE math glfw glad)
    endif()
else()
    target_link_libraries(AURELION PRIVATE math)
endif()
