// #include <glfw3.h>
#include <iostream>
using namespace std;
// void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//     glViewport(0, 0, width, height);
// }

// int main() {
//     if (!glfwInit()) {
//         std::cerr << "Failed to initialize GLFW" << std::endl;
//         return -1;
//     }

//     GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
//     if (!window) {
//         std::cerr << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     glfwMakeContextCurrent(window);
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     while (!glfwWindowShouldClose(window)) {
//         glClear(GL_COLOR_BUFFER_BIT);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwDestroyWindow(window);
//     glfwTerminate();
//     return 0;
// }

int main() {
    cout << "Hello, OpenGL!" << endl;
    return 0;
}