cmake_minimum_required(VERSION 3.12)
project(Detach_Join_Project)
set (CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fcoroutines")

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_library(tutorials 
src/aa_detach_join.cpp
src/ab_join_exception.cpp
src/ac_accumulate.cpp
src/ad_local_global.cpp
src/ae_lockguard.cpp
src/af_deadlock.cpp
src/ag_uniquelock.cpp
src/ah_condition_var.cpp
src/ai_async_future.cpp
src/aj_promise.cpp
src/ak_cxx20_jthread.cpp
src/al_cxx20_boost_barrier.cpp
src/am_cxx20_coroutines.cpp
src/ex1.cpp
src/trial1_template.cpp
)

add_compile_options(-pthread)

target_include_directories(tutorials PUBLIC include)

add_executable(runTutorials src/main.cpp)
target_link_libraries(runTutorials 
pthread
tutorials
${Boost_LIBRARIES} boost_system boost_thread)

# target_include_directories(tutorials PUBLIC tests)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
message("${GTEST_INCLUDE_DIRS}")

add_library(test_cases INTERFACE)
target_include_directories(test_cases INTERFACE tests)

add_executable(runTests tests/test_main.cpp)
target_link_libraries(runTests
test_cases
pthread
tutorials
${Boost_LIBRARIES} boost_system boost_thread GTest::GTest GTest::gmock)
