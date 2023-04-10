#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <numeric>
#include "ac_accumulate/module.h"

void accumulate_test() {
    std::vector<int> v{1,2,3,4,5,6,7,8,9,10};
    int sum = std::accumulate(v.begin(), v.end(), 0);
    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
    auto dash_fold = [](std::string a, int b)
    {
        return std::move(a) + '-' + std::to_string(b);
    };

    std::cout << "sum of vector: " << sum << std::endl;
    std::cout << "product of vector: " << product << std::endl;

    std::string s = std::accumulate(std::next(v.begin()), v.end(),
        std::to_string(v[0]), // start with first element
        dash_fold);

    std::cout << s << std::endl;
}