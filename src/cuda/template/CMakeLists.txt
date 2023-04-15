cmake_minimum_required(VERSION 3.09)
project(Cmake_CUDA_Project LANGUAGES CUDA CXX)
find_package(CUDA REQUIRED)

add_executable(runTemplate main.cu)