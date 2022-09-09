# BitmapTerrain
Terrain generator from a grayscale image.

For now it only works with true grayscale images. To convert any image to this format, I recommend running the following ImageMagick command:

`convert <input_image> -set colorspace Gray -separate -average <output_image.png>`
