# Python: animate Bousing Ball using PlotItem
# convert each scene to QImage and Pillow Image
# create anime gif using Pillow Image
# 2025-04-10  K.OHWADA


import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtWidgets, QtGui
from PIL import Image
from pos import Pos  
from ball import *
import numpy as np
import io
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

GIF_DURATION= 500 # msec

GIF_LOOP= 0 # endless

GIF_OUTFILE = "pg_anime_ball.gif"

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

SAVE_FORMAT = "BMP"


def create_amine_gif(	images):
	images[0].save(GIF_OUTFILE,
	save_all=True,
	append_images = images[1:],
	duration= GIF_DURATION,  
	loop=GIF_LOOP
	)
	print('create ', GIF_OUTFILE)
# end

# https://doloopwhile.hatenablog.com/entry/20100305/1267782841
def qimage2pilimage(qimage):
    buffer =  QtCore.QBuffer()
    buffer.open(QtCore.QIODevice.WriteOnly)
    qimage.save(buffer, SAVE_FORMAT)
    fp = io. BytesIO()
    fp.write(buffer.data().data())
    buffer.close()
    fp.seek(0)
    return Image.open(fp)
# end

def plotitem2qimage(plt, width, height):
    sourceRect = plt.sceneBoundingRect()
    # print('sourceRect: ', sourceRect)
    targetRect = QtCore.QRect(0, 0, width, height)
    scene = plt.scene()
    # print( 'scene: ', type(scene) )
    bgbrush =  scene.views()[0].backgroundBrush()
    bg = bgbrush.color()

    qimg = QtGui.QImage(width, height, QtGui.QImage.Format_RGB32)
    qimg.fill(bg)
    painter = QtGui.QPainter(qimg)
    scene.render(painter, QtCore.QRectF(targetRect), QtCore.QRectF(sourceRect))
    painter.end()
    return qimg
# end

def plotitem2pilimage(plt, width, height):
	qimg = plotitem2qimage(plt, width, height)
	pimg = qimage2pilimage(qimg)
	return pimg
# end


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
        img = Image.open(FPATH_IMG)
        nd_arr = np.array(img)
        arr_270 = np.rot90(	nd_arr, 3)
        self.img_item = pg.ImageItem()
        self.img_item.setImage(arr_270)
        self.plt.addItem(self.img_item)
        self.pos = Pos()
        self.pos.set_range(X_MIN, X_MAX, Y_MIN, Y_MAX)
        self.pos.set_init(X_INIT, Y_INIT, VX, VY)
        self.cnt = 0
        self.images = []
        self.is_append_plt = True
        timer = QtCore.QTimer(self)
        timer.timeout.connect(self.updatePos)
        timer.start(UPDATE_INTERVAL) 
# end

    def updatePos(self):
        x, y =  self.pos.update_pos()
        self.img_item.setPos(x, y)
        if self.is_append_plt:
            if self.cnt < FRAMES:
                self.cnt +=1
                pimg = plotitem2pilimage(self.plt, self.width(), self.height() )
                self.images.append(pimg)
            elif self.cnt == FRAMES:
                self.is_append_plt = False
                create_amine_gif(self.images)
# end


# main
app = pg.mkQApp()
win = Window()
win.show()
sys.exit(app.exec())





