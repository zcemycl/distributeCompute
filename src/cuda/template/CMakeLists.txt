cmake_minimum_required(VERSION 3.09)
project(Cmake_CUDA_Project LANGUAGES CUDA CXX)
find_package(CUDA REQUIRED)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
message("${GTEST_INCLUDE_DIRS}")

add_library(cuda_mod src/module.cu)
target_include_directories(cuda_mod PUBLIC include)

add_executable(runTemplate scripts/main.cu)
target_link_libraries(runTemplate cuda_mod)
add_executable(runTest tests/test.cpp)
target_link_libraries(runTest GTest::GTest cuda_mod)
