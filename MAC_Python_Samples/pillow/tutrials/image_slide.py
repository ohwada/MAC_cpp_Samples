# Python: slide Imge using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image


# slide Image halfway horizontally
def slide_image(fpath):
	name, ext = os.path.splitext(fpath)
	outfile = "pil_tutorial_image_slide_" + name + ext
	print(outfile)
	im = Image.open(fpath)
	iw, ih = im.size
	print(iw, ih)
	delta = (iw//2) % iw
	print('delta: ', delta)
	if delta == 0:
		return
	part1 = im.crop((0, 0, delta, ih))
	part2 = im.crop((delta, 0, iw, ih))
	im.paste(part1, (iw - delta, 0, iw, ih))
	im.paste(part2, (0, 0, (iw - delta), ih))
	im.show()
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
slide_image(fpath)
