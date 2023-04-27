#include <gtest/gtest.h>
#include "ag_sum_arr/module.cuh"

TEST(Sum_Arr_Test, dry_run) {
    play_sum_arr_gpu();
}