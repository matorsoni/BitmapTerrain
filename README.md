# BitmapTerrain

Terrain generator from a grayscale image.

For now it only works with true grayscale images. To convert any image to this format, I recommend running the following ImageMagick command:

`convert <input_image> -set colorspace Gray -separate -average <output_image.png>`

# Setup

Clone repository along with submodules (`-j4` flag is an optional speed up):

`git clone --recurse-submodules -j4 https://github.com/matorsoni/BitmapTerrain.git`


# Samples

Commit 8997092:

![commit_8997092](https://user-images.githubusercontent.com/33296520/189392235-e857b709-d6b5-4bfa-82d3-a9f2b7a691ac.png)
