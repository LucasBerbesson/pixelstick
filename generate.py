import os
from os.path import basename

from PIL import Image


for filename in os.listdir('.'):
   if filename.endswith(".png") or filename.endswith(".jpg"):
        text_file_name = "{}.txt".format(os.path.splitext(filename)[0])
        text_file = open(text_file_name, "w+")
        im = Image.open(filename)
        pixels = list(im.getdata())
        for pixel in pixels:
            try:
                red,green,blue,brightness = pixel
                text_file.write("{}, {}, {}\n".format(red,green,blue))
            except:
                print(text_file_name)
        text_file.write("300, 300, 300")
        text_file.close()
