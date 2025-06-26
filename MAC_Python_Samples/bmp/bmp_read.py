# https://qiita.com/cat2151/items/4cc61731732fa644f762
# Python: load BMP file 
# show Image using matplotlib
# modify: 2025-04-10  K.OHWADA

from bmp import Bmp
import matplotlib.pyplot as plt
import numpy as np
import sys, os

FPATH_IMG = "images/uparrow.bmp"

AXIS = "off"

USAGE_FORMAT = "Usage: python {:s}  <bmp filepath>"


def show_image(fpath):
	bmp = Bmp()
	bmp.readFile(fpath)
	bmp. printHeader()
	print('check: ', bmp.check() )
	width, height, pixels = bmp.getPixels()
	print('pixels: ', width, height)
	img = np.array(pixels)
	print('shape: ', img.shape)
	basename = os.path.basename(fpath)
	plt.figure(num=basename)
	plt.axis(AXIS)
	plt.imshow(img)
	plt.show()
# end

def usage(script):
	usage = USAGE_FORMAT.format(script)
	print(usage)

# main
fpath = FPATH_IMG
args = sys.argv
argc = len(args)
if argc < 2:
	usage(args[0])
else:
	fpath = args[1]
# end
show_image(fpath)
