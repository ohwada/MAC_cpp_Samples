# Python: load Image file with Pillow Image
# show Image in Matplotlib Window
# default Window size : 640x480
# 2025-04-10  K.OHWADA

# https://qiita.com/soiSource/items/e859d57f07847063de4d

import matplotlib.pyplot as plt
from PIL import Image
import numpy as np
import sys, os

AXIS = "off"

def show_image(fpath):
	name, ext = os.path.splitext(fpath)
	outfile = "mat_pil_image_show_" + name + ".png"
	print(outfile)
	basename = os.path.basename(fpath)
	img = Image.open(fpath)
	img_arr = np.array(img)
	plt.figure(num=basename)
	plt.axis(AXIS )
	plt.imshow(img_arr)
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
show_image(fpath)

