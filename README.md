# BitmapTerrain

C++/OpenGL terrain generator from a grayscale image.

## Samples

![image_3](https://user-images.githubusercontent.com/33296520/189945390-5e0fbc76-eed8-4af7-9bf7-7f6e7c2f91aa.png)

![image_4](https://user-images.githubusercontent.com/33296520/189945404-6306ea4c-e2f9-4fe6-a9f6-2ca0004893d8.png)

![image_1](https://user-images.githubusercontent.com/33296520/189945589-657501ce-86bb-40a5-b062-4be4c34328f8.png)

![image_2](https://user-images.githubusercontent.com/33296520/189945623-4fd454ae-ca1c-47fd-bcba-85d7c8920215.png)

![image_5](https://user-images.githubusercontent.com/33296520/189945641-11224e0b-65d5-4a10-9d9a-5d5f3625e45c.png)

![image_6](https://user-images.githubusercontent.com/33296520/189945662-73850058-4c65-4d6a-9446-24b824e124d4.png)


## Setup

Clone repository along with submodules (`-j4` flag is an optional speed up):

`git clone --recurse-submodules -j4 https://github.com/matorsoni/BitmapTerrain.git`

Build and run the project:

```bash
cd BitmapTerrain/
mkdir build
cd build
cmake ..
make -j4
./terrain
```

**Note:** GLFW may ask for additional dependencies that are not installed in your system. Installing them and rebuilding this project should work fine.


## Running the application

Execution modes:

(1) `./terrain`

(2) `./terrain <path-to-grayscale-image.png>`

(3) `./terrain <path-to-grayscale-image.png> <path-to-rgb-texture.jpeg>`

Running (1) will create the default image terrain (`BitmapTerrain/assets/bitmap.png`) renderer with the default texture (`BitmapTerrain/assets/wood.jpeg`).

Running (2) will create a terrain based on input image, renderer with the default texture.

Running (3) will create a terrain based on input image, renderer with the input texture.

**Note:** While textures can be of any image type, terrain generation only works with true grayscale images. To convert any image to this format, I recommend running the following ImageMagick command:

`convert <input_image> -set colorspace Gray -separate -average <output_image.png>`


## Inputs

- Move camera with WASD + mouse movement.
- Mouse scroll to increase and decrease terrain height.
- Press F to render on wireframe mode (On/Off).
- Press T to apply texture (On/Off).
- ESC to close application.
