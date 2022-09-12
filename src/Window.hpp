#ifndef WINDOW_HPP
#define WINDOW_HPP

class GLFWwindow;

// Initialize GLFW. Must be called before constructing a Window object.
GLFWwindow* createWindow(int width, int height);

// Free allocated memory and cleanup.
void cleanupWindow(GLFWwindow* window);

#endif // WINDOW_HPP
