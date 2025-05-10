# Python: image point multiply 20 using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image


# multiply each pixel by 20
def image_point_multiply_20(fpath):
	name, ext = os.path.splitext(fpath)
	outfile =  "pil_tutorial_image_point_multiply_20_" + name + ext
	print(outfile)
	im = Image.open(fpath)
	im2 = im.point(lambda i: i * 20)
	im2.show()
	im2.save(outfile)
# end


def image_point_mask(fpath):
	name, ext = os.path.splitext(fpath)
	outfile =  "pil_tutorial_image_point_mask_" + name + ext
	print(outfile)
	im = Image.open(fpath)
# split the image into individual bands
	source = im.split()
	R, G, B = 0, 1, 2
# select regions where red is less than 100
	mask = source[R].point(lambda i: i < 100 and 255)
# process the green band
	out = source[G].point(lambda i: i * 0.7)
# paste the processed band back, but only where red was < 100
	source[G].paste(out, None, mask)
# build a new multiband image
	im = Image.merge(im.mode, source)
	# im.show()
	im.save(outfile)
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
image_point_mask(fpath)
image_point_multiply_20(fpath)

