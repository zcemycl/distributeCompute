#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "aa_test_install/module.hpp"

const GLint WIDTH = 800, HEIGHT = 600;

int main(int argc, char** argv) {
    test_setup1(argc, argv);

    if (!glfwInit()){
        printf("GLFW initializsation failed!");
        glfwTerminate();
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    return 0;
}