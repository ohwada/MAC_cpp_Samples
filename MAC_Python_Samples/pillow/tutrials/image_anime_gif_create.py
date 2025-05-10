# Python: create amine gif using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image


def create_amine_gif(fpath):
	name, ext = os.path.splitext(fpath)	
	outfile = "pil_tutorial_image_anime_gif_create_" + name + ".gif"
	print(outfile)

	im = Image.open(fpath)
	im90 = im.rotate(90)
	im180 = im.rotate(180)
	im270 = im.rotate(270)

# assume Image i is square.
# rotate clockwise
	images = [
	im,
	im270,
	im180,
	im90
	]

# images[0].save('test.gif', save_all=True,
    #           append_images=images[1:], optimize=False, duration=500, loop=0)

# Save the images as an animated GIF
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
	print("Usage: python %s  <image filepath>" % script)
	exit()
# end

fpath = args[1]
create_amine_gif(fpath)
