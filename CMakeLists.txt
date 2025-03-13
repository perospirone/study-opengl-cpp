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

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include GLAD headers
include_directories(include)

# Find required packages (GLFW, GLEW, OpenGL)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

configure_file(${CMAKE_SOURCE_DIR}/vertex.glsl ${CMAKE_BINARY_DIR}/vertex.glsl COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/fragment.glsl ${CMAKE_BINARY_DIR}/fragment.glsl COPYONLY)

file(GLOB IMAGE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/assets/*.jpg" "${CMAKE_CURRENT_SOURCE_DIR}/assets/*.png")
file(COPY ${IMAGE_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add executable
add_executable(main main.cpp src/glad.c shader_s.h)

# Link libraries
target_link_libraries(main glfw GLEW::GLEW OpenGL::GL glm::glm)
