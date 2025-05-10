# Python: paste Image using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image


# paste fpath2 on fpath1
def paste_image(fpath1, fpath2):
	name1, ext1 = os.path.splitext(fpath1)
	name2, ext2 = os.path.splitext(fpath2)
	outfile =  "pil_tutorial_image_paste_" + name2 + "_on_" +name1 + ext1
	print(outfile)
	im1 = Image.open(fpath1)
	im2 = Image.open(fpath2)
	im1.paste(im2)
	im1.show()
	im1.save(outfile)
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
paste_image(fpath1, fpath2)
