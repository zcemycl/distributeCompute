cmake_minimum_required(VERSION 3.09)
project(Detach_Join_Project)
set (CMAKE_CXX_STANDARD 11)

add_library(tutorials src/aa_detach_join.cpp)

target_include_directories(tutorials PUBLIC include)

add_executable(runTutorials src/main.cpp)
target_link_libraries(runTutorials pthread tutorials)