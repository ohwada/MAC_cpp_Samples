# Python: show Image in QVGA size Window using matplotlib and Pillow
# 2025-04-10  K.OHWADA

# https://stackoverflow.com/questions/28816046/displaying-different-images-with-actual-size-in-matplotlib-subplot

import matplotlib.pyplot as plt
from PIL import Image
import numpy as np
import sys, os

# QVGA
WIDTH = 320
HEIGHT = 240

DPI = 100.0

AXIS = "off"


def show_image_in_qvga(fpath):
	basename = os.path.basename(fpath)
	figsize = ( float(WIDTH/ DPI), float(HEIGHT / DPI) )
	plt.figure(num=basename, figsize=figsize )
	plt.axis(AXIS)
	img = Image.open(fpath)
	img_arr = np.array(img)	
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
show_image_in_qvga(fpath)

