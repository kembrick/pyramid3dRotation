cmake_minimum_required(VERSION 3.17)
project(pyramid3dRotation)

set(CMAKE_CXX_STANDARD 26)
set(OpenGlLinkers -lglut -lGLU -lGL)
add_executable(pyramid3dRotation main.cpp source/rigidBody.h source/show3d.h source/operations.h)
target_link_libraries(pyramid3dRotation ${OpenGlLinkers})