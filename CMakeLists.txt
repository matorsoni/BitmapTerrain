cmake_minimum_required(VERSION 3.10)

project(BitmapTerrain)

# Define C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    terrain
    src/Main.cpp
)
