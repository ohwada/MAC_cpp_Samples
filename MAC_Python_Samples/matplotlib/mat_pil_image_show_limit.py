# Python: load Image file with Pillow Image
# show Image in Matplotlib Window
# default Window size : 640x480
# 2025-04-10  K.OHWADA


import matplotlib.pyplot as plt
from PIL import Image
import numpy as np
import sys, os

WIDTH = 480
HEIGHT = 360

DPI = 100.0

FIGSIZE = ( float(WIDTH/ DPI), float(HEIGHT / DPI) )

AXIS = "off"

USAGE_FORMAT = "Usage: python {:s}  <image filepath> [limit] [resize]"


def resize_image(img):
	iw, ih = img.size
	print('img: ', iw, ih)
	ratio_w = WIDTH/iw
	ratio_h = HEIGHT/ih
	ratio = min(ratio_w, ratio_h)
	if ( iw > WIDTH ) or ( ih > HEIGHT):
		w = int(ratio * iw)
		h = int(ratio * ih)
		print('resize: ', w, h)
		img = img.resize( (w, h) )
# end
	return img
# end

def load_image(fpath, is_resize):
	img = Image.open(fpath)
	if is_resize:
		img = resize_image(img)
# end
	return img
# end

def show_image(fpath, is_limit, is_resize):
	basename = os.path.basename(fpath)
	plt.figure(num=basename, figsize=FIGSIZE)
	# plt.axis(AXIS )
	if is_limit:
		plt.xlim(0, WIDTH)
		plt.ylim(HEIGHT, 0)
# end
	img = load_image(fpath, is_resize)
	img_arr = np.array(img)
	plt.imshow(img_arr)
	plt.show()
# end


def usage(script):
	usage= USAGE_FORMAT.format(script)
	print(usage)
# end


# main
fpath = ""
is_limit = False
is_resize = False
args = sys.argv
argc = len(args)
if argc < 2:
	usage(args[0])
	exit()
elif argc >= 4:
	fpath = args[1]
	is_limit = int(args[2])
	is_resize = int(args[3])
elif argc >= 3:
	fpath = args[1]
	is_limit = int(args[2])
elif argc >= 2:
	fpath = args[1]
# end
show_image(fpath, is_limit, is_resize)

