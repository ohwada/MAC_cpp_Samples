# Python: animate Bousing Ball using PlotItem
# write each scene as bmp image file
# create anime gif using Pillow Image
# 2025-04-10  K.OHWADA


import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtWidgets, QtGui
from PIL import Image
from pos import Pos  
from ball import *
import numpy as np
import glob
import sys, os


WIN_TITLE = "Bousing Ball"
PX = 10
PY = 10
WIDTH = 480
HEIGHT = 360

BOTTOM = "bottom"
LEFT =  "left"

# Anim
UPDATE_INTERVAL = 500 # msec

FRAMES = 120 # 60 sec

DIR_BALL = "ball"

FNAME_FORMAT = "ball_{:03d}.bmp"

GLOB_PATHNAME = "ball/*.bmp"

GIF_DURATION= 500 # msec

GIF_LOOP= 0 # endless

GIF_OUTFILE = "pg_anime_ball_write.gif"

WHITE = (255, 255, 255)
BLUE =  (0, 0, 255)

# ball rect
rect =  getRect(WIDTH, HEIGHT, 0.2, 0.9, 0.1, 0.9)

RECT = rect

X_MIN = rect.left()

X_MAX = rect.right() - BALL_SIZE

Y_MIN = rect.top()

Y_MAX = rect.bottom()  - BALL_SIZE

X_INIT = X_MIN

Y_INIT = Y_MAX

VX= Pos.VX

VY = - Pos.VY


def create_amine_gif():
	file_list = sorted(glob.glob(GLOB_PATHNAME))
	images = []
	for f in file_list:
		if  os.path.isfile(f):
			im = Image.open(f)
			images.append(im)
# end
# save the images as an animated GIF
	images[0].save(GIF_OUTFILE,
	save_all=True,
	append_images = images[1:],
	duration= GIF_DURATION,  
	loop=GIF_LOOP
	)
	print('create ', GIF_OUTFILE)
# end


def pilimage2ImageItem(pimg):
	nd_arr = np.array(pimg)
# ImageItem is rotated 90 degrees for col-major is the default
# rotated 270 degrees so that it is displayed in the correct orientation when rotated.
	arr_270 = np.rot90(	nd_arr, 3)
	img_item = pg.ImageItem()
	img_item.setImage(arr_270)
	return img_item
# def


class Window(pg.GraphicsLayoutWidget):
	def __init__(self):
		super().__init__()
		self.setWindowTitle(WIN_TITLE)
		self.setGeometry( PX, PY, WIDTH, HEIGHT)
		self.setBackground(WHITE)
		pg.setConfigOptions(antialias=True)
		self.initPlot()
		self.startAnim()
# end

	def initPlot(self):
		self.plt = self.addPlot()
		self.plt.setRange(xRange = (0, WIDTH), yRange = (0,  HEIGHT))
		self.plt.showAxis(BOTTOM, False)
		self.plt.showAxis(LEFT, False)
		self.drawRect(self.plt)
# end

	def drawRect(self, plt):
		pen_blue = pg.mkPen(BLUE, width=1)
		rect = QtCore.QRectF(RECT)
		rect_item = QtWidgets.QGraphicsRectItem(rect)
		rect_item.setPen( pen_blue)
		plt.addItem(rect_item)
# end

	def startAnim(self):
		pimg = Image.open(FPATH_IMG)
		self.img_item = pilimage2ImageItem(pimg)
		self.plt.addItem(self.img_item)
		self.pos = Pos()
		self.pos.set_range(X_MIN, X_MAX, Y_MIN, Y_MAX)
		self.pos.set_init(X_INIT, Y_INIT, VX, VY)
		self.cnt = 0
		self.is_save_plt = True
		os.mkdir(DIR_BALL)
		timer = QtCore.QTimer(self)
		timer.timeout.connect(self.updatePos)
		timer.start(UPDATE_INTERVAL) 
# end

	def updatePos(self):
		x, y =  self.pos.update_pos()
		self.img_item.setPos(x, y)
		if self.is_save_plt:
			if self.cnt < FRAMES:
				self.cnt +=1
				self.save_plot(self.plt, self.cnt)
			elif self.cnt == FRAMES:
				self.is_save_plt = False
				create_amine_gif()
# end

	def save_plot(self, plt, cnt):
		fname = FNAME_FORMAT.format(cnt)
		outfile = os.path.join(DIR_BALL, fname)
		plt.writeImage(outfile)
# end


# main
app = pg.mkQApp()
win = Window()
win.show()
sys.exit(app.exec())





