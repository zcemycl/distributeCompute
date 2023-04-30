#include <gtest/gtest.h>
#include "ak_profile_driven_optimise_nvprof/module.cuh"

TEST(Grid1D_Block1D, dry_run) {
    char* parameters[] = {};
    run_sum_array_1d(0, parameters);
}

TEST(Grid2D_Block2D, dry_run) {
    char* parameters[] = {};
    run_sum_array_2d(0, parameters);
}