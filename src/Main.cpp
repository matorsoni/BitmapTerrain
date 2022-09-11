#include <iostream>
#include <string>

// Macro to avoid GLFW including OpenGL header on it's own.
// Ref: https://www.glfw.org/docs/3.3/quick.html#quick_include
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// Include OpenGL function declarations from GLAD.
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Bitmap.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"
#include "ShaderProgram.hpp"

using std::cout;
using std::endl;
using std::string;

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

// Parse arguments. Possible inputs are:
// - No inputs -> Render default image (../assets/bitmap.png).
// - Path to image -> Render input image.
string parseArguments(int argc, char** argv)
{
    if (argc == 1) {
        return "../assets/bitmap.png";
    }
    else if (argc == 2) {
        return argv[1];
    }
    else {
        cout << "Only 1 argument is accepted." << endl;
        return "";
    }
}

int main(int argc, char** argv)
{
    string path_to_img = parseArguments(argc, argv);
    if (path_to_img.size() == 0) {
        return -1;
    }

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

    // Create basic shader program.
    const auto program = ShaderProgram("../src/shader/Vert.glsl",
                                       "../src/shader/Frag.glsl");

    // Create terrain mesh.
    Mesh terrain;
    {
        Bitmap bitmap;
        auto success = bitmap.loadFromFile(path_to_img);
        if (!success) {
            cout << "Failed loading image from file: " << path_to_img << endl;
            return -1;
        }

        createBitmapMesh(terrain, bitmap.data(), bitmap.width(), bitmap.height());
    }

    // Define camera position and orientation.
    Camera camera(window_width, window_height);
    camera.lookAt(glm::vec3(0.0f, 0.0f, 0.0f));

    MeshRenderer renderer;
    renderer.updateMesh(terrain);

    // Main loop.
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        processInput(window);

        renderer.draw(camera, program);

        glfwSwapBuffers(window);
    }

    // GLFW cleanup.
    glfwDestroyWindow(window);
    glfwTerminate();
}
