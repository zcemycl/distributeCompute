#include <iostream>
#include "aa_detach_join/module.h"
#include "ab_join_exception/module.h"
#include "ac_accumulate/module.h"
#include "ad_local_global/module.h"
#include "ae_lockguard/module.h"
#include "af_deadlock/module.h"
#include "ag_uniquelock/module.h"
#include "ah_condition_var/module.h"
#include "ai_async_future/module.h"
#include "ex1/module.h"
#include "trial1_template/module.h"

int main() {
    // detach_join();
    // join_exception();
    // accumulate_test();
    // local_global_test();
    // lock_test();
    // deadlock_test();
    // unique_lock_test();
    // naive_bus_arrival();
    // condition_var_bus_arrival();
    async_future_play();
    // ex1();
    // try_template();
    
    return 0;
}