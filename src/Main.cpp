#include <iostream>

// Macro to avoid GLFW including OpenGL header on it's own.
// Ref: https://www.glfw.org/docs/3.3/quick.html#quick_include
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// Include OpenGL function declarations from GLAD.
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Camera.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"

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
    // Background color.
    glClearColor(0.0f, 0.15f, 0.15, 1.0f);
    // Render on wireframe or fill mode.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Log useful info.
    cout << "OpenGL version " << glGetString(GL_VERSION) << endl;
    cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << endl;

    // Create basic shader program.
    const auto program = ShaderProgram("../src/shader/Vert.glsl",
                                       "../src/shader/Frag.glsl");
    program.use();

    // Mesh creation.
    Mesh square;
    unsigned char bitmap[256] = {66, 10, 20, 102, 221, 189, 179, 63, 106, 165, 150, 81, 235, 37, 243, 215, 122, 137, 178, 41, 93, 245, 254, 159, 123, 139, 242, 226, 114, 126, 238, 89, 47, 223, 86, 141, 32, 171, 225, 84, 85, 231, 153, 130, 96, 110, 194, 146, 239, 175, 185, 253, 27, 144, 214, 70, 109, 103, 187, 115, 35, 19, 203, 252, 202, 108, 22, 72, 12, 79, 28, 191, 97, 1, 255, 204, 161, 163, 131, 125, 113, 212, 249, 180, 23, 220, 90, 30, 2, 107, 206, 11, 209, 21, 217, 190, 162, 129, 157, 38, 154, 152, 184, 156, 173, 207, 134, 140, 116, 151, 169, 120, 33, 117, 127, 196, 236, 201, 135, 40, 8, 147, 247, 219, 172, 248, 65, 124, 48, 4, 167, 82, 44, 211, 71, 3, 91, 45, 176, 55, 133, 56, 6, 39, 164, 208, 105, 5, 168, 43, 192, 246, 26, 7, 177, 13, 112, 251, 68, 29, 54, 197, 64, 136, 49, 233, 145, 52, 76, 50, 210, 77, 121, 148, 234, 73, 213, 80, 9, 83, 128, 244, 0, 59, 42, 75, 111, 155, 237, 95, 100, 227, 60, 195, 160, 92, 18, 241, 88, 67, 101, 198, 51, 200, 31, 15, 104, 170, 174, 34, 183, 142, 94, 250, 205, 149, 16, 46, 230, 158, 229, 17, 74, 78, 240, 193, 57, 69, 58, 182, 222, 138, 224, 232, 132, 181, 61, 216, 186, 14, 199, 188, 143, 25, 166, 218, 118, 98, 87, 36, 119, 99, 228, 53, 24, 62};
    createBitmapMesh(square, bitmap, 18, 18);

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    unsigned int ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 square.vertices.size() * sizeof(Vertex),
                 square.vertices.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 square.indices.size() * sizeof(unsigned int),
                 square.indices.data(),
                 GL_STATIC_DRAW);

    glm::mat4 model(1.0f);

    Camera camera;
    camera.lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    camera.updateView();

    program.setUniformMat4f("Model", model);
    program.setUniformMat4f("View", camera.view());
    program.setUniformMat4f("Projection", camera.projection());

    // Main loop.
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window);

        glDrawElements(GL_TRIANGLES, square.indices.size(), GL_UNSIGNED_INT, (void*)0);

        glfwSwapBuffers(window);
    }

    // GLFW cleanup.
    glfwDestroyWindow(window);
    glfwTerminate();
}
