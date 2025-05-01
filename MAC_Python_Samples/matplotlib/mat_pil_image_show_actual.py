# Python: show image in _actual size using matplotlib and pillow
# 2025-04-10  K.OHWADA

# https://stackoverflow.com/questions/28816046/displaying-different-images-with-actual-size-in-matplotlib-subplot

from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import sys
import os


DPI = float(80)

AXIS = "off"


def display_image_in_actual_size(fpath):
    fname = os.path.basename(fpath)
    img = plt.imread(fpath)
    ih, iw, depth = img.shape
    print(iw, ih, depth)    
# What size does the figure need to be in inches to fit the image?
    figsize = (iw / DPI, ih / DPI)
    fig = plt.figure(num=fname,  figsize=figsize)
    ax = fig.add_axes([0, 0, 1, 1])
    ax.axis(AXIS)
    ax.imshow(img)
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
display_image_in_actual_size(fpath)

