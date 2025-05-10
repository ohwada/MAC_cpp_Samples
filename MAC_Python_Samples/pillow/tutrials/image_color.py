# Python: split and merge color using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image

	
def split_merge_color(fpath):
	name, ext = os.path.splitext(fpath)
	outfile = "pil_tutorial_image_color_bgr_" + name + ext
	print(outfile)
	im = Image.open(fpath)
	imode = im.mode
	print(imode)
	if imode == "RGBA":
		r, g, b, a = im.split()
	elif imode == "RGB":
		r, g, b = im.split()
# end
	im2 = Image.merge("RGB", (b, g, r))
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
split_merge_color(fpath)
