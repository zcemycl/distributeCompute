#include <gtest/gtest.h>
#include "ah_device_prop/module.cuh"

TEST(Device_Props_Test, dry_run) {
    query_device();
}