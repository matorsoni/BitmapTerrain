#include "InputHandler.hpp"

// Macro to avoid GLFW including OpenGL header on it's own.
// Ref: https://www.glfw.org/docs/3.3/quick.html#quick_include
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "MeshRenderer.hpp"

InputHandler HANDLER;

void InputHandler::assertionCheck()
{
    assert(camera_ptr);
    assert(renderer_ptr);
}

// Callback that listens to mouse movement and translate it to camera turning.
static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    HANDLER.assertionCheck();

    // Last position declared as static to save its state in each iteration.
    static float last_x = HANDLER.window_width / 2;
    static float last_y = HANDLER.window_height / 2;
    float delta_x = xpos - last_x;
    float delta_y = ypos - last_y;

    static constexpr float sensitivity = 0.1f;
    float delta_pitch = -delta_y * sensitivity;
    float delta_yaw = -delta_x * sensitivity;
    HANDLER.camera_ptr->turn(delta_pitch, delta_yaw);

    last_x = xpos;
    last_y = ypos;
}

// Callback that listens to keyboard press. Usually used for text input, so it's behavior is
// not ideal for continuous camera movement, for example.
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    HANDLER.assertionCheck();

    if (key == GLFW_KEY_F && action == GLFW_PRESS)
        HANDLER.renderer_ptr->toggleWireframeOnOff();
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
        HANDLER.renderer_ptr->toggleTextureOnOff();
}

// Callback that listens to mouse scroll event.
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    HANDLER.assertionCheck();
    static constexpr float sensitivity = 0.1f;
    HANDLER.renderer_ptr->controlYScale(yoffset * sensitivity);
}

void setInputCallbacks(GLFWwindow* window)
{
    // Lock the cursor and make it invisible.
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

void processCallbackEvents()
{
    // Poll events and execute the corresponding callback functions defined above.
    glfwPollEvents();
}

void processNonCallbackEvents(GLFWwindow* window)
{
    HANDLER.assertionCheck();

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
