#include "InputHandler.hpp"

// Macro to avoid GLFW including OpenGL header on it's own.
// Ref: https://www.glfw.org/docs/3.3/quick.html#quick_include
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Camera.hpp"

InputHandler HANDLER;

// Callback that listens to mouse movement and translate it to camera turning.
static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static float last_x = HANDLER.window_width / 2;
    static float last_y = HANDLER.window_height / 2;
    float delta_x = xpos - last_x;
    float delta_y = ypos - last_y;

    const static float sensitivity = 0.1f;
    float delta_pitch = -delta_y * sensitivity;
    float delta_yaw = -delta_x * sensitivity;
    HANDLER.camera_ptr->turn(delta_pitch, delta_yaw);

    last_x = xpos;
    last_y = ypos;
}

void setInputCallbacks(GLFWwindow* window)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
}

void processCallbackEvents()
{
    // Poll events and execute the corresponding callback functions defined above.
    glfwPollEvents();
}

void processNonCallbackEvents(GLFWwindow* window)
{
    // ESC key closes the application.
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    // Check for WASD inputs and translate it to camera movement.
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        HANDLER.camera_ptr->moveForwards();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        HANDLER.camera_ptr->moveBackwards();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        HANDLER.camera_ptr->moveRight();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        HANDLER.camera_ptr->moveLeft();
}
