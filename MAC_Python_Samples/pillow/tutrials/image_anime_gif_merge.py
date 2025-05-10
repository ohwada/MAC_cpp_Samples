# Python: merge images to create amine gif using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image


def merge_images_to_create_amine_gif(dir_name):
	outfile = dir_name + "_merge_anime.gif"
	print(outfile)

	images = []

# assume the file names are in the order you want to play.
	for fname in os.listdir(dir_name):
		fpath = os.path.join(dir_name, fname)
		if  os.path.isfile(fpath):
			im = Image.open(fpath)
			images.append(im)
# end

# save the images as an animated GIF
	images[0].save(outfile,
	save_all=True,
	append_images = images[1:],
	duration=500,  # duration of each frame in milliseconds
	loop=0 # loop forever
	)
# end


# main
args = sys.argv
argc = len(args)
script = args[0]

if argc < 2:
	print("Usage: python %s  <image dir name>" % script)
	exit()
# end

dir_name = args[1]
merge_images_to_create_amine_gif(dir_name)

