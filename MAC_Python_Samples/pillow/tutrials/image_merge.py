# Python: merge Images using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image


def merge_image(fpath1, fpath2):
	name1, ext1 = os.path.splitext(fpath1)
	name2, ext2 = os.path.splitext(fpath2)
	outfile =   "pil_tutorial_image_merge_" + name1 + "_" + name2 + ext1
	print(outfile)
	im1 = Image.open(fpath1)
	iw1, ih1 = im1.size
	print(iw1, ih1)
	im2 = Image.open(fpath2)
	iw2, ih2 = im2.size
	print(iw2, ih2)
	w = iw1 + iw2
	h = max(ih1, ih2)
	im = Image.new("RGBA", (w, h))
	im.paste(im1)
	im.paste(im2, (iw1, 0))
	im.show()
	im.save(outfile)
# end


# main
args = sys.argv
argc = len(args)
script = args[0]

if argc < 3:
	print("Usage: python %s  <image1 filepath>  <image2 filepath>" % script)
	exit()
# end

fpath1 = args[1]
fpath2 = args[2]
merge_image(fpath1, fpath2)
