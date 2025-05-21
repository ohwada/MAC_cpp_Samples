# Python: show Image in actual size using matplotlib and Pillow
# 2025-04-10  K.OHWADA

# https://stackoverflow.com/questions/28816046/displaying-different-images-with-actual-size-in-matplotlib-subplot

import matplotlib.pyplot as plt
from PIL import Image
import numpy as np
import sys, os


DPI = 100.0

AXIS = "off"


def show_image_in_actual_size(fpath):
    basename = os.path.basename(fpath)
    img = Image.open(fpath)
    iw, ih = img.size
    print(iw, ih)
    img_arr = np.array(img)

# What size does the figure need to be in inches to fit the image?
    figsize = ( float(iw / DPI), float(ih / DPI) )
    plt.figure(num=basename,  figsize=figsize)

    plt.axis(AXIS)
    plt.imshow(img_arr)
    plt.show()
# end


# main
args = sys.argv
argc = len(args)
script = args[0]

if argc < 2:
	print("Usage: python %s  <image filepath>" % script)
	exit()
# end

fpath = args[1]
# show_image(fpath)
show_image_in_actual_size(fpath)

