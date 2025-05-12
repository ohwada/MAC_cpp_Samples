# Python: show Image in Matplotlib Window using Pillow and Matplotlib
# default Window size : 640x480
# 2025-04-10  K.OHWADA

# https://qiita.com/soiSource/items/e859d57f07847063de4d

from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
import sys
import os


# resize
WIDTH = 300
HEIGHT = 300

AXIS = "off"

# name_width x height.png
FORMAT = "pil_mat_image_show_resize_{}_{}x{}.png"

def resize_image(fpath):
	is_resize = False
	img = Image.open(fpath)
	iw, ih = img.size 
	print('img: ', iw, ih)
	ratio_w = WIDTH/iw
	ratio_h = HEIGHT/ih
	ratio = min(ratio_w, ratio_h)
	if ( iw > WIDTH ) or ( ih > HEIGHT):
		is_resize = True
		w = int(ratio * iw)
		h = int(ratio * ih)
		print('resize: ', w, h)
		img = img.resize( (w, h) )
	# end
	return [is_resize, img]

def show_resize_image_in_matplotlib_window_save(fpath):
	basename = os.path.basename(fpath)
	name, ext = os.path.splitext(fpath)
	outfile = "pil_mat_image_show_resize_" + name + ".png"
	print(outfile)
	is_resize, img = resize_image(fpath)
	img_np = np.array(img)
	plt.figure(num=basename)
	plt.axis(AXIS )
	plt.imshow(img_np)
	plt.savefig(outfile)
	if is_resize:
		iw, ih = img.size 
		fname = FORMAT.format(name, iw, ih)
		print(fname)
		img.save(fname)
# end
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
show_resize_image_in_matplotlib_window_save(fpath)

