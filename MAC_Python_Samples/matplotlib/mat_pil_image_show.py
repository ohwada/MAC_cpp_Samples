# Python: show image using matplotlib and pillow
# 2025-04-10  K.OHWADA

# https://qiita.com/soiSource/items/e859d57f07847063de4d

from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import sys
import os

WIDTH = 400

HEIGHT = 400

DPI = 100

AXIS = "off"

def show_image(fpath):
	img = Image.open(fpath)
	img_np = np.array(img)
	fname = os.path.basename(fpath)
	w = WIDTH/DPI
	h =  HEIGHT/DPI
	plt.figure(num=fname, figsize=(w, h))
	plt.axis(AXIS )
	plt.imshow(img_np)
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

