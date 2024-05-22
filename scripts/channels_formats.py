from PIL import Image
import sys

def check_image_format(image_path):
    try:
        with Image.open(image_path) as img:
            mode = img.mode
            format = img.format
            size = img.size
            
            if mode == "L":
                num_channels = 1  # Grayscale
                opengl_format = "GL_RED"
            elif mode == "LA":
                num_channels = 2  # Grayscale + Alpha
                opengl_format = "GL_RG"
            elif mode == "RGB":
                num_channels = 3  # RGB
                opengl_format = "GL_RGB"
            elif mode == "RGBA":
                num_channels = 4  # RGBA
                opengl_format = "GL_RGBA"
            else:
                num_channels = len(mode)  # Other modes like "CMYK"
                opengl_format = "Unknown or not directly supported"

            print(f"Image Format: {format}")
            print(f"Image Size: {size}")
            print(f"Number of Channels: {num_channels}")
            print(f"OpenGL Format: {opengl_format}")
    
    except IOError:
        print(f"Cannot open image file: {image_path}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python check_image_format.py <image_path>")
    else:
        image_path = sys.argv[1]
        check_image_format(image_path)
