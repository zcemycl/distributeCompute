cmake_minimum_required(VERSION 3.09)
project(Cmake_CUDA_Project LANGUAGES CUDA CXX)
find_package(CUDA REQUIRED)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
message("${GTEST_INCLUDE_DIRS}")

add_executable(runTemplate main.cu module.cu)
add_executable(runTest test.cpp module.cu)
target_link_libraries(runTest GTest::GTest)
