#include <gtest/gtest.h>
// #include <gmock/gmock.h>
#include "aa_basic_hello/module.cuh"
#include <iostream>
#include <cmath>

TEST(Basic_Hello_Cuda, dry_run) {
    play_hello_cuda();
}