# Python: load Image file using Pollow Image
# show Image using PlotIrem and ImageItem
# If Image size is large than  Window size
# show image reduced to fit in Window
 # suport jpeg
#  2025-04-10  K.OHWADA


import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtWidgets, QtGui
import pyqtgraph.exporters as  exporters
from PIL import Image
import numpy as np
import sys, os


PX = 10
PY = 10
WIDTH = 480
HEIGHT = 360

BOTTOM = "bottom"
LEFT =  "left"

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)

USAGE_FORMAT = "Usage: python {:s}  <image filepath> [set Range] [resize]"


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

def load_image(fpath, is_resize):
		img = Image.open(fpath)
		if is_resize:
			img = resize_image(img)
# end
		return img
# end


class Window(pg.GraphicsLayoutWidget):
	def __init__(self):
		super().__init__()
		self.setGeometry( PX, PY, WIDTH, HEIGHT)
		self.setBackground(WHITE)
		pg.setConfigOptions(antialias=True)
# end

	def init_plot(self, is_range):
		plt = self.addPlot()
		#plt.showAxis(BOTTOM, False)
		#plt.showAxis(LEFT, False) 
		if is_range:
			print('.setRange')
			plt.setRange(xRange = (0, WIDTH), yRange = (0,  HEIGHT))
# end
		return plt
# end

	def set_fpath(self, fpath, is_range, is_resize):
		basename = os.path.basename(fpath)
		self.setWindowTitle(basename)
		img = load_image(fpath, is_resize)
		nd_arr = np.array(img)
		nd_arr270 = np.rot90(nd_arr, 3)
		img_item = pg.ImageItem()
		img_item.setImage(nd_arr270)
		plt = self.init_plot(is_range)
		plt.addItem(img_item)
# end


def main(fpath, is_range, is_resize):
    app = pg.mkQApp()
    win = Window()
    win.set_fpath(fpath, is_range, is_resize)
    win.show()
    sys.exit(app.exec())
# end


def usage(script):
    usage = USAGE_FORMAT.format(script)
    print(usage)
# end


# main
fpath = ""
is_range = False
is_resize = False
args = sys.argv
argc = len(args)
if argc < 2:
	usage(args[0])
	exit()
elif argc >= 4:
	fpath = args[1]
	is_range = int(args[2])
	is_resize = int(args[3])
elif argc >= 3:
	fpath = args[1]
	is_range = int(args[2])
elif argc >= 2:
	fpath = args[1]
# end
main(fpath, is_range, is_resize)


