# Python: Image Enhance using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image, ImageEnhance


def image_enhance(fpath):
	name, ext = os.path.splitext(fpath)
	prefix =  "pil_tutorial_image_enhance_"
	fname_contrast =  prefix  + "contrast_" + name + ext
	print(fname_contrast)
	fname_brightness =  prefix  + "brightness_" + name + ext
	print(fname_brightness)
	fname_sharpness =  prefix  + "sharpness_" + name + ext
	print(fname_sharpness)
	fname_color =  prefix  + "color_" + name + ext
	print(fname_color)
	im = Image.open(fpath)
	enh1 = ImageEnhance.Contrast(im)
	enh1.enhance(1.3).save(fname_contrast)
	enh2 = ImageEnhance.Brightness(im)
	enh2.enhance(1.3).save(fname_brightness)
	enh3 = ImageEnhance.Sharpness(im)
	enh3.enhance(1.3).save(fname_sharpness)
	enh4 = ImageEnhance.Color(im)
	enh4.enhance(1.3).save(fname_color)
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
image_enhance(fpath)
