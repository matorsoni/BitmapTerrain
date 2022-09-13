#include <cassert>
#include <iostream>
#include <string>

#include "Bitmap.hpp"
#include "Camera.hpp"
#include "InputHandler.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"
#include "Texture.hpp"
#include "Window.hpp"

using std::cout;
using std::endl;
using std::string;

// Parse arguments. Possible inputs are:
// - No inputs -> Render default image (../assets/bitmap.png).
// - 1 Path to image -> Render input image.
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

    // Create window.
    const int window_width = 1280;
    const int window_height = 720;
    GLFWwindow* window = createWindow(window_width, window_height);
    if (window == nullptr) {
        return -1;
    }

    // Create terrain mesh from grayscale bitmap.
    Mesh terrain;
    {
        Bitmap bitmap;
        auto success = bitmap.loadFromFile(path_to_img);
        if (!success) {
            cout << "Failed loading image from file: " << path_to_img << endl;
            return -1;
        }

        assert(bitmap.channels() == 1);
        createBitmapMesh(terrain, bitmap.data(), bitmap.width(), bitmap.height());
    }

    // Create texture.
    Texture texture;
    {
        Bitmap bitmap;
        string path_to_tex("../assets/wood.jpeg");
        auto success = bitmap.loadFromFile(path_to_tex, true);
        if (!success) {
            cout << "Failed loading image from file: " << path_to_tex << endl;
            return -1;
        }

        texture.create(bitmap.data(), bitmap.width(), bitmap.height(), bitmap.channels());
    }

    // Create camera.
    Camera camera(window_width, window_height);

    // Create renderer.
    MeshRenderer renderer;
    renderer.pushMesh(terrain);
    renderer.setTexture(texture);

    // Setup input handler, passing every object that will respond to external inputs.
    HANDLER.window_width = window_width;
    HANDLER.window_height = window_height;
    HANDLER.camera_ptr = &camera;
    HANDLER.renderer_ptr = &renderer;
    setInputCallbacks(window);

    // Main loop.
    while(!shouldClose(window)) {
        processCallbackEvents();
        processNonCallbackEvents(window);

        renderer.draw(camera);

        swapBuffers(window);
    }

    cleanupWindow(window);
}
