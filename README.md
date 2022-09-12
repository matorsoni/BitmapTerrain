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

Note: GLFW may ask for additional dependencies that are not installed in your system. Installing them and rebuilding this project should work fine.

Running `./terrain` with no arguments will use the default image found in `BitmapTerrain/assets`.
You can generate the terrain with other grayscale images by passing a valid image path as argument:

`./terrain <path-to-image.png>`


For now it only works with true grayscale images. To convert any image to this format, I recommend running the following ImageMagick command:

`convert <input_image> -set colorspace Gray -separate -average <output_image.png>`

## Inputs

- WASD for camera movement.
- Mouse movement to rotate camera.
- Press F to render on wireframe mode (On/Off).

# Samples

Commit 8997092:

![commit_8997092](https://user-images.githubusercontent.com/33296520/189392235-e857b709-d6b5-4bfa-82d3-a9f2b7a691ac.png)
