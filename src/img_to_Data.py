import PIL
import array
from PIL import Image
import os
from pathlib import Path
import numpy as np

# i = Image.open("src.png")
# i = i.convert("RGB")

# pixels = i.load() # this is not a list, nor is it list()'able
# width, height = i.size

# all_pixels = []
# for x in range(width):
#     for y in range(height):
#         cpixel = pixels[x, y]
#         print(cpixel)
#         all_pixels.append(cpixel)

# # exit()

img_paths = []
imgs = []

img_dir = "img"
out_file_data_cpp = "src/led_matrix_data.cpp"
out_file_color_cpp = "src/led_matrix_color_data.cpp"
out_file_data_h = "include/led_matrix_data.h"
out_file_color_h = "include/led_matrix_color_data.h"


def idx_to_pos(n, y_len = 8):
    """Für 8x32 Grid
        x_len . . .
        y_len
        .
        .
        .
    """
    row = n // y_len
    up_row = row % 2

    x = row
    y = n % y_len
    if up_row:
        y = y_len-1 - y

    return (x,y)


def pos_to_idx(x,y, y_len=8):
    n_row = x * y_len
    up_row = x % 2

    if up_row:
        n = n_row + y_len - 1 - y
    else:
        n = n_row + y

    return n


def pixel_to_data(pix, out_name, n_pix):
    lines = f"byte {out_name}[] = " + "{\n"
    for i in range(0, n_pix):
        px,py = idx_to_pos(i)
        if i % 8 == 0 and i != 0:
            lines += "\n"
        if np.mean(pix[px,py]) > 127: lines += "1, "
        else: lines += "0, "
    lines += "};\n\n"
    return lines




def pixel_to_color_data(pix, out_name, n_pix):
    """
    32 Bit, WRGB each 8-Bit in this order MSB White, LSB Blue
    """
    lines = f"uint32_t {out_name}[] = " + "{\n"
    for i in range(0, n_pix):
        px,py = idx_to_pos(i)
        if i % 8 == 0 and i != 0:
            lines += "\n"
        lines += f"{(((pix[px,py][0]<<16)+(pix[px,py][1]<<8)+pix[px,py][2])):#08x}, "

    lines += "};\n"
    return lines



def image_to_c_data():
    for file in os.listdir(img_dir):
        if file.endswith(".png"):
            img_paths.append(os.path.join(img_dir, file))

    for img_path in img_paths:
        imgs.append(Image.open(img_path))

    # print("found images:",img_paths)
    img_tup : tuple[Image.Image,str] = zip(imgs,img_paths)

    lines_data_cpp = ""
    lines_data_h = ""
    lines_color_cpp = ""
    lines_color_h = ""

    lines_data_h += "#ifndef LED_MATRIX_DATA_H\n" \
                    "#define LED_MATRIX_DATA_H\n" \
                    "#include <Arduino.h>\n\n"
    lines_data_cpp += "#include \"led_matrix_data.h\"\n"

    lines_color_h +="#ifndef LED_MATRIX_COLOR_DATA_H\n" \
                    "#define LED_MATRIX_COLOR_DATA_H\n" \
                    "#include <Arduino.h>\n\n"
    lines_color_cpp += "#include \"led_matrix_color_data.h\"\n"    

    for img, img_path in img_tup:
        symbol_name = Path(img_path).stem
        symbol_name = symbol_name.replace("Ä","AE")
        symbol_name = symbol_name.replace("Ü","UE")
        symbol_name = symbol_name.replace("Ö","OE")
        
        img : Image.Image = img.convert("RGB")
        pix = img.load()
        print(img_path,img.size, symbol_name)
        img_n_pix = img.width*img.height
        
        # Data output
        lines_data_cpp += pixel_to_data(pix, symbol_name, img.width*img.height)
        lines_data_cpp += f"size_t {symbol_name}_size = {img_n_pix} * sizeof(byte);\n\n"

        lines_data_h += f"extern byte {symbol_name}[];\n"
        lines_data_h += f"extern size_t {symbol_name}_size;\n"

        symbol_name = symbol_name+"_color"
        # Color Data output
        lines_color_cpp += pixel_to_color_data(pix, symbol_name, img.width*img.height)
        lines_color_cpp += f"size_t {symbol_name}_size =  {img_n_pix} * sizeof(uint32_t);\n\n"

        lines_color_h += f"extern uint32_t {symbol_name}[];\n"
        lines_color_h += f"extern size_t {symbol_name}_size;\n"

        img.close()

    lines_data_h += "#endif"
    lines_color_h += "#endif"

    with open(out_file_data_h,"wt") as out:
        out.write(lines_data_h)
    with open(out_file_data_cpp,"wt") as out:
        out.write(lines_data_cpp)
    with open(out_file_color_h,"wt") as out:
        out.write(lines_color_h)
    with open(out_file_color_cpp,"wt") as out:
        out.write(lines_color_cpp)


if __name__ == "__main__":
    # for i in range(-20,0):
    # print(pos_to_idx(32-11,1))
    image_to_c_data()

