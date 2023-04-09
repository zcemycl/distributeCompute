#include <iostream>
#include "trial1_template/module.h"

using namespace std;

template<typename T>
T add(T num1, T num2) {
    return num1 + num2;
}

template<>
string add(string num1, string num2){
    return to_string(stod(num1) + stod(num2));
}

void try_template() {
    std::cout << add<int>(1, 2) << std::endl;
    std::cout << add<double>(1.4, 2.5) << std::endl;
    std::cout << add<string>("1.4", "2.5") << std::endl;
}