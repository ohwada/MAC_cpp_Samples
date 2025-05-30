# Python: show resized Image using Pillow 
# If Image size is larger than the specified size, resize Image
# 2025-04-10  K.OHWADA

# https://www.kikagaku.co.jp/kikagaku-blog/pillow/#i-3

from PIL import Image
import sys
import os

# resize
WIDTH = 300
HEIGHT = 300

# name_width x height.png
FORMAT = "pil_image_show_resize_{:s}_{:d}x{:d}.png"

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
# end

def show_resize_image_save(fpath):
	name, ext = os.path.splitext(fpath)
	is_resize, img = resize_image(fpath)
	if is_resize:
		iw, ih = img.size 
		fname = FORMAT.format(name, iw, ih)
		print(fname)
		# img.save(fname)
# end
	img.show()
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
show_resize_image_save(fpath)