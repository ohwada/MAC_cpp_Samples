# Python: load Image file with  Matplotlib imread
# show Image in Matplotlib Window
# suport jpeg
# default Window size : 640x480
# imread
# https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.imread.html
# This function exists for historical reasons. 
# It is recommended to use PIL.Image.open instead for loading images.
# 2025-04-10  K.OHWADA

# https://zerofromlight.com/blogs/detail/98/

import matplotlib.pyplot as plt
import sys
import os


# hide all axis labels
# https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.axis.html
AXIS = "off"


# default Window size : 640x480
def show_image_in_default(fpath):
	basename = os.path.basename(fpath)
	name = os.path.splitext(fpath)[0]
	outfile = "mat_image_show_" + name + ".png"
	print(outfile)
	plt.figure(num=basename)
	plt.axis(AXIS )

# imread
# https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.imread.html
# It is recommended to use PIL.Image.open instead for loading images.
	img = plt.imread(fpath)

	plt.imshow(img)
	# plt.savefig(outfile)
	plt.show()
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
show_image_in_default(fpath)

