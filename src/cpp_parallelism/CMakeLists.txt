cmake_minimum_required(VERSION 3.09)
project(Detach_Join_Project)
set (CMAKE_CXX_STANDARD 17)

add_library(tutorials 
src/aa_detach_join.cpp
src/ab_join_exception.cpp
src/ac_accumulate.cpp
src/ad_local_global.cpp
src/ae_lockguard.cpp
src/af_deadlock.cpp
src/ag_uniquelock.cpp
src/ex1.cpp
src/trial1_template.cpp
)

target_include_directories(tutorials PUBLIC include)

add_executable(runTutorials src/main.cpp)
target_link_libraries(runTutorials pthread tutorials)