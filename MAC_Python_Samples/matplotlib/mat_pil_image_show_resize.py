# Python: show image in _actual size using matplotlib and pillow
# 2025-04-10  K.OHWADA

# https://stackoverflow.com/questions/28816046/displaying-different-images-with-actual-size-in-matplotlib-subplot

from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

# resize
WIDTH = 400
HEIGHT = 400

AXIS = "off"


def get_image_resize(fpath):
	img = Image.open(fpath)
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


def show_resized_image(fpath):
	basename = os.path.basename(fpath)
	img =  get_image_resize(fpath)
	img_np = np.array(img)
	fig = plt.figure(num=basename)
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
show_resized_image(fpath)


