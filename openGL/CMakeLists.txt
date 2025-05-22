cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)
# set(glfw3_DIR "C:/Users/trieu.phan/Downloads/glfw-3.4/CMake")

# Add source files
add_executable(OpenGLProject src/main.cpp)

# Link OpenGL and GLFW
# find_package(OpenGL REQUIRED)
# find_package(glfw3 REQUIRED)

# target_link_libraries(OpenGLProject OpenGL::GL glfw)
# target_compile_definitions(OpenGLProject PRIVATE
#     GLFW_INCLUDE_NONE
# )