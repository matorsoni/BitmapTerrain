#ifndef WINDOW_HPP
#define WINDOW_HPP

class Camera;
class GLFWwindow;

// Initialize GLFW. Must be called before constructing a Window object.
GLFWwindow* createWindow(int width, int height);

// Free allocated memory and cleanup.
void cleanupWindow(GLFWwindow* window);

class Control
{
public:
    Camera* camera_ptr;
};

extern Control control;

void setInputCallbacks(GLFWwindow* window);

#endif // WINDOW_HPP
