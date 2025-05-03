# Python: show image in _actual size using matplotlib and pillow
# 2025-04-10  K.OHWADA

# https://stackoverflow.com/questions/28816046/displaying-different-images-with-actual-size-in-matplotlib-subplot

from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import sys
import os

# QVGA
WIDTH = 320
HEIGHT = 240

DPI = 100.0

AXIS = "off"


def display_image_in_qvga(fpath):
	fname = os.path.basename(fpath)
	img = Image.open(fpath)
	img_np = np.array(img)
	figsize = ( (WIDTH/ DPI), (HEIGHT / DPI))
	fig = plt.figure(num=fname, figsize=figsize )
	plt.axis(AXIS)
	plt.imshow(img_np)
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
display_image_in_qvga(fpath)

