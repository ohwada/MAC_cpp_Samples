# Python: show amine gif using Pillow and Matplotlib
# 2025-04-10  K.OHWADA


from PIL import Image, ImageSequence
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import os, sys


INTERVAL=100  #100ms

# hide axis
AXIS = 'off'


def split_amine_gif(fpath):
	img = Image.open(fpath)
	list_frames = ImageSequence.Iterator(img)
	ims = []
	for frame in list_frames:
		arr = np.array(frame)
		im = plt.imshow(arr)
		ims.append( [im] )
# end
	return ims
# end


def show_amine_gif(fpath):
	basename = os.path.basename(fpath)
	fig = plt.figure(num=basename)
	ims = split_amine_gif(fpath)
	num = len(ims)
	print(basename, ':', num, 'frames')
	anim = animation.ArtistAnimation(fig, ims, INTERVAL)
	plt.axis(AXIS)
	plt.show()
# end


# main
args = sys.argv
argc = len(args)
script = args[0]

if argc < 2:
	print("Usage: python %s  <anime gif filepath>" % script)
	exit()
# end

fpath = args[1]
show_amine_gif(fpath)

