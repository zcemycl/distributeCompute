#include "aj_warp_divergence/module.cuh"
#include "ak_profile_driven_optimise_nvprof/module.cuh"
#include <stdexcept>
#include <iostream>
#include <string>

#include <unordered_map>

const static std::unordered_map<std::string,int> string_to_case {
    {"aj", 1},
    {"ak-1d", 2},
    {"ak-2d", 3},
};

int main(int argc, char** argv) {

    if (argc < 1)
        throw std::invalid_argument("Not enough arguments ... ");
    
    if (! string_to_case.contains(argv[1]))
        throw std::invalid_argument("Invalid case of execution ... ");

    switch (string_to_case.at(argv[1])) {
        case 1:
            test_warp_divergence();
        case 2:
            run_sum_array_1d(argc, argv);
        case 3:
            run_sum_array_2d(argc, argv);
        default:
            ;
    }
    

    return 0;
}