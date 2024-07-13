import PIL
import array
from PIL import Image


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

img = Image.open('stripes.png')
img = img.convert("RGB")
pix = img.load()
print(img.size)
lines = "const byte stripes[] PROGMEM = {\n  "
pixels = ""
for py in range(0,img.size[1]):
    for px in range(0,img.size[0]):
        pixels+=str(pix[px,py])
        print(pix[px,py])
        lines+=f"{(pix[px,py][0]):#04x},{pix[px,py][1]:#04x},{pix[px,py][2]:#04x}"
        if((px != img.size[0]-1) | (py != img.size[1]-1)):
            lines+=","
        
        lines+=" "
        #else:
            #print(str(px)+" "+str(py)+" "+str(int(img.size[1]-1))+""+str(pix[py,py]))
    # lines+=" 0x00, 0x00,\n"
    lines+="\n"
    pixels+="\n"
    if(py != img.size[1]-1):
        lines+="  "
lines += "};"
out = open("out.txt","wt")
print(lines)
# print(pixels)
out.write(lines)
out.close()
img.close()