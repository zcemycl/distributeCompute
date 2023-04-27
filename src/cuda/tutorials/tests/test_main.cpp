#include <gtest/gtest.h>
// #include <gmock/gmock.h>
#include "test_aa_basic_hello.hpp"
#include "test_ab_threadidx.hpp"
#include "test_ac_blockgrid.hpp"
#include "test_ad_1darr.hpp"
#include "test_ae_2darr.hpp"
#include "test_af_3darr.hpp"
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}