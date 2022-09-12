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
    deps/glad/src/glad.c
    src/Main.cpp
    src/Bitmap.cpp
    src/Camera.cpp
    src/Mesh.cpp
    src/MeshRenderer.cpp
    src/ShaderProgram.cpp
    src/Window.cpp
)

target_include_directories(
    terrain
    PRIVATE
        deps/glad/include
        deps/glfw/include
        deps/glm
        deps/stb
)

target_link_libraries(
    terrain
    glfw
)
