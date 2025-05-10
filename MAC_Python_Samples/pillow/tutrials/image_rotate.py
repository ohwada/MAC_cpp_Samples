# Python: rotete Imge using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image


def rotate_image(fpath):
	name, ext = os.path.splitext(fpath)
	prefix = "pil_tutorial_image_rotate_"
	fname_45 = prefix + "45_" + name + ext
	print(fname_45)
	fname_90 = prefix + "90_"+ name + ext
	print(fname_90)
	fname_180 = prefix + "180_" + name + ext
	print(fname_180)
	fname_270 = prefix  + "270_" + name + ext
	print(fname_270)
	im = Image.open(fpath)
	im.rotate(45).save(fname_45)
	im.rotate(90).save(fname_90)
	im.rotate(180).save(fname_180)
	im.rotate(270).save(fname_270)
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
rotate_image(fpath)
