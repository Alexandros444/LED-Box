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
out_file = "include/led_matrix_data.h"


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


def pixel_to_data(pix, out_name):
    lines = f"byte {out_name}[] = " + "{\n"
    for i in range(0, img.width*img.height):
        px,py = idx_to_pos(i)
        if i % 8 == 0 and i != 0:
            lines += "\n"
        if np.mean(pix[px,py]) > 127: lines += "1, "
        else: lines += "0, "
    lines += "};\n\n"
    return lines




def pixel_to_Color_data(pix, out_name):
    """
    32 Bit, WRGB each 8-Bit in this order MSB White, LSB Blue
    """
    lines = f"uint32_t {out_name}[] = " + "{\n"
    for i in range(0, img.width*img.height):
        px,py = idx_to_pos(i)
        if i % 8 == 0 and i != 0:
            lines += "\n"
        lines += f"{(((pix[px,py][0]<<16)+(pix[px,py][1]<<8)+pix[px,py][2])):#08x}, "

    lines += "};\n"
    return lines




for file in os.listdir(img_dir):
    if file.endswith(".png"):
        img_paths.append(os.path.join(img_dir, file))

for img_path in img_paths:
    imgs.append(Image.open(img_path))

# print("found images:",img_paths)
img_tup : tuple[Image.Image,str] = zip(imgs,img_paths)

with open(out_file,"wt") as out:
    out.write("#ifndef byte\n#include <Arduino.h>\n#endif\n\n")

for img, img_path in img_tup:
    symbol_name = Path(img_path).stem
    
    img : Image.Image = img.convert("RGB")
    pix = img.load()
    print(img_path,img.size)
    
    lines = pixel_to_Color_data(pix, symbol_name)
    lines += f"size_t {symbol_name}_size = sizeof({symbol_name}) / sizeof({symbol_name}[0]);\n"
    lines += "\n"

    with open(out_file,"at") as out:
        out.write(lines)
    
    img.close()




if __name__ == "__main__":
    pass
    # for i in range(0,24):
    #     print(idx_to_pos(i,5))

