# Python: plit amine gif using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image, ImageSequence


def split_amine_gif(fpath):
	name, ext = os.path.splitext(fpath)
	os.mkdir(name)
	im = Image.open(fpath)
	cnt = 0
	for frame in ImageSequence.Iterator(im):
		cnt += 1
		fname = name + "_" + str(cnt) + ".gif"
		path  = os.path.join(name, fname)
		print(path)
		frame.save(path)
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
split_amine_gif(fpath)
