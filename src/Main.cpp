#include <iostream>

// Macro to avoid GLFW including OpenGL header on it's own.
// Ref: https://www.glfw.org/docs/3.3/quick.html#quick_include
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
// Include OpenGL function declarations from GLAD.
#include "glad/glad.h"

using std::cout;
using std::endl;

// Create GLFW error callback function.
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error: %s\n", description);
}

// Process inputs with GLFW.
static void processInput(GLFWwindow* window)
{
    // ESC key closes the application.
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    // Initialize GLFW with error callback.
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW." << endl;
        return -1;
    }

    // Set minimum OpenGL core profile version expected by the context.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create window.
    const int window_width = 1280;
    const int window_height = 720;
    GLFWwindow* window = glfwCreateWindow(window_width,
                                          window_height,
                                          "BitmapTerrain",
                                          NULL,
                                          NULL);
    if (!window) {
        cout << "Failed to create window." << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to create OpenGL context." << endl;
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1);
    glClearColor(0.0f, 0.15f, 0.15, 1.0f);

    // Log useful info.
    cout << "OpenGL version " << glGetString(GL_VERSION) << endl;
    cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << endl;

    // Main loop.
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window);

        glfwSwapBuffers(window);
    }

    // GLFW cleanup.
    glfwDestroyWindow(window);
    glfwTerminate();
}
