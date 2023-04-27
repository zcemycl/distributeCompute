cmake_minimum_required(VERSION 3.10)
project(CUDA_Tutorials LANGUAGES CUDA CXX)
find_package(CUDA REQUIRED)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
message("${GTEST_INCLUDE_DIRS}")

add_library(tutorials
src/aa_basic_hello.cu
src/ab_threadidx.cu
src/ac_blockgrid.cu
src/ad_1darr.cu
src/ae_2darr.cu
src/af_3darr.cu
src/ag_sum_arr.cu
)
target_include_directories(tutorials PUBLIC include)

add_library(test_cases INTERFACE)
target_include_directories(test_cases INTERFACE tests)

add_executable(runTests tests/test_main.cpp)
target_link_libraries(runTests
test_cases
GTest::GTest
tutorials)