#include <gtest/gtest.h>
#include "test_aa_detach_join.hpp"
#include "test_ab_join_exception.hpp"
#include "test_ac_accumulate.hpp"
#include "test_ad_local_global.hpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
