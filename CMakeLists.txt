# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(study-opengl-cpp VERSION 1.0)

# Prefer GLVND over legacy OpenGL
set(OpenGL_GL_PREFERENCE GLVND)

# Prefer static libraries
#set(BUILD_SHARED_LIBS OFF)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages (GLFW, GLEW, OpenGL)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# Add executable
add_executable(main main.cpp)

# Link libraries
target_link_libraries(main glfw GLEW::GLEW OpenGL::GL)
