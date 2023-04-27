#include "common.hpp"
#include <iostream>

void compare_arrs(int * a, int * b, int size){
    for (int i=0; i<size; i++){
        if (a[i]!=b[i]){
            std::cout << "Arrays are different ... " << std::endl;
            return;
        }
    }
    std::cout << "Arrays are same ... " << std::endl;
}