cmake_minimum_required(VERSION 3.12)
project(Detach_Join_Project)
set (CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# set(JTHREAD_FOUND 1)
# set(JTHREAD_INCLUDE_DIRS "/opt/homebrew/Cellar/jthread/1.3.3/include")
# set(JTHREAD_LIBRARIES  "-L/opt/homebrew/Cellar/jthread/1.3.3/lib" "-ljthread")
# include_directories(${JTHREAD_INCLUDE_DIRS})
# include_directories(/opt/homebrew/Cellar/jthread/1.3.3/lib)

# find_package(Boost)
# include_directories(${Boost_INCLUDE_DIRS})

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
src/ex1.cpp
src/trial1_template.cpp
)

add_compile_options(-pthread)

target_include_directories(tutorials PUBLIC include)

add_executable(runTutorials src/main.cpp)
target_link_libraries(runTutorials pthread tutorials Threads::Threads)