#include <gtest/gtest.h>
// #include <gmock/gmock.h>
#include "test_aa_basic_hello.hpp"
#include "test_ab_threadidx.hpp"
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}