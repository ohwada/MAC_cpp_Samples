# https://github.com/pyqtgraph/pyqtgraph/blob/master/pyqtgraph/examples/ImageItem.py
# Python: load Image file using Pollow Image
# show Image using ViewBox and ImageItem
# If Image size is large than  Window size
# show image reduced to fit in Window
 # suport jpeg
#  modify: 2025-04-10  K.OHWADA


import pyqtgraph as pg
from PIL import Image
import numpy as np
import sys, os


# Window
PX = 50
PY = 50
WIDTH = 480
HEIGHT = 360

WHITE = (256, 256, 256)

USAGE_FORMAT =	 "Usage: python {:s}  <image filepath> [resize]"

def resize_image(img):
	iw, ih = img.size 
	print('img: ', iw, ih)
	ratio_w = WIDTH/iw
	ratio_h = HEIGHT/ih
	ratio = min(ratio_w, ratio_h)
	if ( iw > WIDTH ) or ( ih > HEIGHT):
		w = int(ratio * iw)
		h = int(ratio * ih)
		print('resize: ', w, h)
		img = img.resize( (w, h) )
	# end
	return img
# end


class Window(pg.GraphicsLayoutWidget):
	def __init__(self):
		super().__init__()
		self.setGeometry(PX, PY, WIDTH, HEIGHT)
		self.setBackground(WHITE)
# end

	def set_ndarray(self, nd_arr):
# ImageItem is rotated 90 degrees for col-major is the default
# rotated 270 degrees so that it is displayed in the correct orientation when rotated.
		arr_270 = np.rot90(	nd_arr, 3)
		view = self.addViewBox()
		img_item = pg.ImageItem()
		img_item.setImage(arr_270)
		view.addItem(img_item)
# def

	def set_fpath(self, fpath,  is_resize):
		basename = os.path.basename(fpath)
		self.setWindowTitle(basename)
		img = Image.open(fpath)
		if is_resize:
			img = resize_image(img)
# end
		nd_arr = np.array(img)
		self.set_ndarray(nd_arr)
# end


def main(fpath,  is_resize):
	app = pg.mkQApp()
	win = Window()
	win.set_fpath(fpath,  is_resize)
	win.show()
	app.exec()
# end


def usage(script):
	usage  = USAGE_FORMAT.format(script)
	print(usage)
# end


# main
is_resize =False
args = sys.argv
argc = len(args)
if argc < 2:
	usage( args[0])
	exit()
elif argc >= 3:
    fpath = args[1]
    is_resize = int(args[2])
elif argc >= 2:
    fpath = args[1]
# end
main(fpath, is_resize)
