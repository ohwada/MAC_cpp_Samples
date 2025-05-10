# Python: convert to Jpeg using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image


def convert_jpeg(fpath):
	name, ext = os.path.splitext(fpath)
	outfile = "pil_tutorial_image_jpeg_" + name + ".jpg"
	if fpath != outfile:
		print(outfile)
		try:
			with Image.open(fpath) as im:
				im2 = im.convert("RGB") # for png
				im2.save(outfile,  "JPEG" ,quality=75)
		except OSError:
			print("cannot convert: ", fpath)
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
convert_jpeg(fpath)