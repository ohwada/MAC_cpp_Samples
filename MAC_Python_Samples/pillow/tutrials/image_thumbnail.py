# Python: create Thumbnail using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image

SIZE = (128, 128)

def create_thumbnail(fpath):
	name, ext = os.path.splitext(fpath)
	outfile = "pil_tutorial_image_thumbnail_" + name + ext
	if fpath != outfile:
		print(outfile)
		try:
			with Image.open(fpath) as im:
				im.thumbnail(SIZE)
				im.save(outfile)
		except OSError:
			print("cannot create thumbnail for: ", fpath)
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
create_thumbnail(fpath)
