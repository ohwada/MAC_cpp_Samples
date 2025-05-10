# Python: convert grey scale using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image


def  convert_grey_scale(fpath):
	name, ext = os.path.splitext(fpath)
	outfile = "pil_tutorial_image_grey_" + name + ext
	print(outfile)
	im = Image.open(fpath)
	im2 = im.convert("L")
	im2.show()
	im2.save(outfile)
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
convert_grey_scale(fpath)
