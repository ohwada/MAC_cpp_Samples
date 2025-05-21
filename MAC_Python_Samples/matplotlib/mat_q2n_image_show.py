# Python: load Image file with qimage2ndarray imread
# show Image in Matplotlib Window
# support jpeg
# 2025-04-10  K.OHWADA

# https://hmeine.github.io/qimage2ndarray/

import matplotlib.pyplot as plt
from qimage2ndarray import imread
import sys
import os


# hide all axis labels
AXIS = "off"


def show_image(fpath):
	basename = os.path.basename(fpath)
	plt.figure(num=basename)
	plt.axis(AXIS )
	img = imread(fpath)
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
show_image(fpath)

