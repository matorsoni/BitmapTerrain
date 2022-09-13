# BitmapTerrain

Terrain generator from a grayscale image.

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

# Samples

Commit 8997092:

![commit_8997092](https://user-images.githubusercontent.com/33296520/189392235-e857b709-d6b5-4bfa-82d3-a9f2b7a691ac.png)
