# Python: show Image in actual size using matplotlib 
# 2025-04-10  K.OHWADA

# https://stackoverflow.com/questions/28816046/displaying-different-images-with-actual-size-in-matplotlib-subplot

import matplotlib.pyplot as plt
import sys
import os


DPI = 80.0

AXIS = "off"


def show_image_in_actual_size(fpath):
    basename = os.path.basename(fpath)
    img = plt.imread(fpath)
    ih, iw, depth = img.shape
    print(iw, ih, depth)    
# What size does the figure need to be in inches to fit the image?
    figsize = ( int(iw / DPI), int(ih / DPI) )
    plt.figure(num=basename,  figsize=figsize)
    plt.axis(AXIS)
    plt.imshow(img)
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

