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

ODER_ROW_MAJOR ="row-major"

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)

USAGE_FORMAT = "Usage: python {:s}  <image filepath> [order row-major] [invertY] [rotate 270] [resize]"


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


def pilimage2ImageItem(pimg, is_rotate, is_order_row):
	nd_arr = np.array(pimg)
	if is_rotate:
		print('rotate 270')
		nd_arr = np.rot90(nd_arr, 3)
# end
	img_item = pg.ImageItem()
	if is_order_row:
		print('oder row-major')
		img_item.setImage(nd_arr, axisOrder=ODER_ROW_MAJOR)
	else:
		img_item.setImage(nd_arr)
# end
	return img_item
# end


class Window(pg.GraphicsLayoutWidget):
	def __init__(self):
		super().__init__()
		self.setGeometry( PX, PY, WIDTH, HEIGHT)
		self.setBackground(WHITE)
		pg.setConfigOptions(antialias=True)
# end

	def set_ImageItem(self, img_item, is_inverty):
		brush_red = pg.mkBrush(RED)
		plt = self.addPlot()
		#plt.showAxis(BOTTOM, False)
		#plt.showAxis(LEFT, False) 
		if is_inverty:
			print('invertY')
			plt.invertY(True)
# end
		img_item.setPos(10, 10)
		plt.addItem(img_item)
		rect = QtWidgets.QGraphicsRectItem(QtCore.QRectF(10,10,5,5))
		rect.setBrush(brush_red)
		plt.addItem(rect)
# end

	def set_fpath(self, fpath, is_order_row, is_inverty,  is_rotate, is_resize):
		basename = os.path.basename(fpath)
		self.setWindowTitle(basename)
		img = Image.open(fpath)
		if is_resize:
			img = resize_image(img)
# end
		img_item = pilimage2ImageItem(img, is_rotate, is_order_row)
		self.set_ImageItem(img_item, is_inverty)
# end


def main(fpath, is_order_row, is_inverty,  is_rotate, is_resize):
    app = pg.mkQApp()
    win = Window()
    win.set_fpath(fpath, is_order_row, is_inverty,  is_rotate, is_resize)
    win.show()
    sys.exit(app.exec())
# end


def usage(script):
    usage = USAGE_FORMAT.format(script)
    print(usage)
# end


# main
fpath = ""
is_order_row = False
is_inverty = False
is_rotate = False
is_resize = False
args = sys.argv
argc = len(args)
if argc < 2:
	usage(args[0])
	exit()
elif argc >= 6:
	fpath = args[1]
	is_order_row = int(args[2])
	is_inverty = int(args[3])
	is_rotate = int(args[4])
	is_resize = int(args[5])
elif argc >= 5:
	fpath = args[1]
	is_order_row = int(args[2])
	is_inverty = int(args[3])
	is_rotate = int(args[4])
elif argc >= 4:
	fpath = args[1]
	is_order_row = int(args[2])
	is_inverty = int(args[3])
elif argc >= 3:
	fpath = args[1]
	is_order_row = int(args[2])
elif argc >= 2:
	fpath = args[1]
# end
main(fpath, is_order_row, is_inverty, is_rotate, is_resize)




