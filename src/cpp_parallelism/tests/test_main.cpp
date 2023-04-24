#include <gtest/gtest.h>
#include "test_aa_detach_join.hpp"
#include "test_ab_join_exception.hpp"
#include "test_ac_accumulate.hpp"
#include "test_ad_local_global.hpp"
#include "test_ae_lockguard.hpp"
#include "test_af_deadlock.hpp"
#include "test_ag_uniquelock.hpp"
// #include "test_ah_condition_var.hpp" // run forever
#include "test_ai_async_future.hpp"
#include "test_aj_promise.hpp"
#include "test_ak_cxx20_jthread.hpp"
#include "test_al_cxx20_boost_barrier.hpp"
#include "test_am_cxx20_coroutines.hpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
