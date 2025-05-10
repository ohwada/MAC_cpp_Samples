# Python: crop Image using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image


# crop the center in half widthwise and lengthwise 
def get_crop_box(fpath):
	im = Image.open(fpath)
	iw, ih = im.size
	x1 = iw// 4
	y1 = ih// 4
	x2 = 3*x1
	y2 = 3*y1
	box =  (x1, y1, x2, y2)
	return box
# end


# crop the center in half widthwise and lengthwise 
def crop_image(fpath):
	name, ext = os.path.splitext(fpath)
	outfile =  "pil_tutorial_image_crop_" + name + ext
	print(outfile)

	im = Image.open(fpath)
	box = get_crop_box(fpath)
	im2 = im.crop(box)
	im2.show()
	im2.save(outfile)
# end


# crop the center in half widthwise and lengthwise 
# rotate the crop part 180 degrees 
# paste the part back onto the original IImage
def crop_rotate_paste(fpath):
	name, ext = os.path.splitext(fpath)
	outfile =  "pil_tutorial_image_crop_rotate_paste_" + name + ext
	print(outfile)
	im = Image.open(fpath)
	box = 	box = get_crop_box(fpath)
	crop = im.crop(box)
	crop2 = crop.transpose(Image.Transpose.ROTATE_180)
	im.paste(crop2, box)
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
crop_rotate_paste(fpath)
crop_image(fpath)
