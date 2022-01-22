cmake_minimum_required(VERSION 3.17)
project(cg_opengl_ini)

set(CMAKE_CXX_STANDARD 14) # a vossa versao

add_executable(cg_opengl_ini main.cpp RgbImage.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(OPENGL_INCLUDE_DIRS ${GLUT_INCLUDE_DIRS})
target_link_libraries(cg_opengl_ini libopengl32.a libglu32.a libfreeglut.a)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)


