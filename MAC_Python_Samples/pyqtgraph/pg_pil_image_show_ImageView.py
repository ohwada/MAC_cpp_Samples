# https://github.com/pyqtgraph/pyqtgraph/blob/master/pyqtgraph/examples/ImageView.py# Python: load Image file using Pillow Image
# Python: show Image using PyQtGraph ImageView
# this is unfinished
# TDO: change background color, hide aixs
# modify: 2025-04-10  K.OHWADA


import pyqtgraph as pg
from PIL import Image
import numpy as np
import sys
import os

# Window
PX = 50
PY = 50
WIDTH = 480
HEIGHT = 360

WHITE = (255, 255, 255)

USAGE_FORMAT =	 "Usage: python {:s}  <image filepath>"


def load_resize_image(fpath):
	img = Image.open(fpath)
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


class Window(pg.QtWidgets.QMainWindow):
	def __init__(self):
		super().__init__()
		self.setGeometry(PX, PY, WIDTH, HEIGHT)
# end

	def set_ndarray(self, nd_arr):
		imv = pg.ImageView()
		imv.setImage(nd_arr) 
		self.setCentralWidget(imv)
# end

	def set_fpath(self, fpath):
		basename = os.path.basename(fpath)
		self.setWindowTitle(basename)
		pilimg = load_resize_image(fpath)
		nd_arr = np.array(pilimg)
		self.set_ndarray(nd_arr)
# end


def main(fpath):
	app = pg.mkQApp()
	pg.setConfigOptions(imageAxisOrder='row-major')
	win = Window()
	win.set_fpath(fpath)
	win.show()
	app.exec()
# end


def usage(script):
	usage  = USAGE_FORMAT.format(script)
	print(usage)
# end


# main
args = sys.argv
argc = len(args)
if argc < 2:
	usage(args[0])
	exit()
# end
main(args[1])

