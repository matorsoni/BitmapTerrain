#include "Window.hpp"

#include <cassert>
#include <iostream>

// Macro to avoid GLFW including OpenGL header on it's own.
// Ref: https://www.glfw.org/docs/3.3/quick.html#quick_include
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// Include OpenGL functions from GLAD instead.
#include <glad/glad.h>

using std::cout;
using std::endl;

// GLFW error callback function.
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error: %s\n", description);
}

GLFWwindow* createWindow(int width, int height)
{
    // Initialize GLFW with error callback.
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW." << endl;
        return nullptr;
    }

    // Set minimum OpenGL core profile version expected by the context.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create window.
    GLFWwindow* window_ptr = glfwCreateWindow(width,
                                              height,
                                              "BitmapTerrain",
                                              NULL,
                                              NULL);
    if (!window_ptr) {
        cout << "Failed to create GLFW window." << endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window_ptr);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to create OpenGL context." << endl;
        glfwTerminate();
        return nullptr;
    }

    glfwSwapInterval(1);

    return window_ptr;
}

void cleanupWindow(GLFWwindow* window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
