#include <gtest/gtest.h>
// #include <gmock/gmock.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "module.cuh"
#include <iostream>

 
TEST(SquareArrTest, Random) {
    float* a_host;
    const unsigned int numElements = 100;
    size_t size = numElements*sizeof(float);
    a_host = new float[size];
    a_host[0] = 10.0;
    a_host[1] = 13.0;
    
    std::cout << a_host[0] << " " << a_host[1] << std::endl;
    test(a_host, numElements);
    std::cout << a_host[0] << " " << a_host[1] << std::endl;

}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}