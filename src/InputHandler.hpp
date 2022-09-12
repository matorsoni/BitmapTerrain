#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

class Camera;
class GLFWwindow;

// InputHandler is a struct meant to be defined as a global variable, which will centralize
// external inputs and modify objects accordingly.
// Examples: move camera, change render parameters.
struct InputHandler
{
    int window_width;
    int window_height;
    Camera* camera_ptr;
};

// Declaration of the global instance of InputHandler. Actual instantance is in the ".cpp" file.
extern InputHandler HANDLER;

// Set external input callbacks via GLFW.
void setInputCallbacks(GLFWwindow* window);

// Process two types of external inputs: those handled with callbacks (less CPU intensive),
// and those handled directly each frame.
// For more info: https://www.glfw.org/docs/3.3/input_guide.html
void processCallbackEvents();
void processNonCallbackEvents(GLFWwindow* window);

#endif // INPUT_HANDLER_HPP
