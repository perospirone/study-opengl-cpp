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

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party)

# Find required packages (GLFW, GLEW, OpenGL)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

# copy shaders
configure_file(${CMAKE_SOURCE_DIR}/src/shaders/vertex.glsl ${CMAKE_BINARY_DIR}/shaders/vertex.glsl COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/shaders/fragment.glsl ${CMAKE_BINARY_DIR}/shaders/fragment.glsl COPYONLY)

# copy images/textures
file(GLOB IMAGE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/assets/*.jpg" "${CMAKE_CURRENT_SOURCE_DIR}/assets/*.png" "${CMAKE_CURRENT_SOURCE_DIR}/assets/*.jpeg")
file(COPY ${IMAGE_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# include project headers
include_directories(src)

# automatically find all source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

# automatically find all header directories
file(GLOB_RECURSE HEADER_DIRS 
    LIST_DIRECTORIES true 
    "src/*.h" 
    "src/*.hpp"
)

# Add executable
add_executable(main ${SOURCES} ${HEADER_DIRS} third_party/glad/glad.c)

target_sources(main PRIVATE
    third_party/imgui/imgui.cpp
    third_party/imgui/imgui_demo.cpp
    third_party/imgui/imgui_draw.cpp
    third_party/imgui/imgui_tables.cpp
    third_party/imgui/imgui_widgets.cpp
    third_party/imgui/backends/imgui_impl_glfw.cpp
    third_party/imgui/backends/imgui_impl_opengl3.cpp
)



# Link libraries
target_link_libraries(main glfw OpenGL::GL glm::glm imgui)
