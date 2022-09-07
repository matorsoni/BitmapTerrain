cmake_minimum_required(VERSION 3.10)

project(BitmapTerrain)

# Define C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Build GLFW
add_subdirectory(deps/glfw)

# Add `terrain` executable.
add_executable(
    terrain
    src/Main.cpp
)

target_include_directories(
    terrain
    PRIVATE
        deps/glfw/include
)

target_link_libraries(
    terrain
    glfw
)
