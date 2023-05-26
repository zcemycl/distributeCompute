cmake_minimum_required(VERSION 3.12)
project(GLFW_Project LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
include_directories(
    ${OPENGL_INCLUDE_DIRS} 
    ${GLUT_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW3_INCLUDE_DIRS}
)

add_library(tutorials
src/aa_test_install.cpp
)

target_include_directories(tutorials PUBLIC include)

add_executable(runTutorials src/main.cpp)
target_link_libraries(runTutorials 
tutorials
${OPENGL_LIBRARIES} ${GLUT_LIBRARY}
glfw
${GLEW_LIBRARIES}
)
