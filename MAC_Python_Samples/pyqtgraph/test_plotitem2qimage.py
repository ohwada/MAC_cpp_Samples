# Python: test for plotitem2qimage()
# 2025-04-10  K.OHWADA


import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtWidgets, QtGui
import sys, os


WIN_TITLE = "test PlotItem_to QImage"
PX = 10
PY = 10
WIDTH = 480
HEIGHT = 360


WHITE =  (255, 255, 255)
BLACK =  (0, 0, 0)
CYAN =  (0, 255, 255)

OUTFILE = "pg_test_ plotitem_to_qimage.png"


def plotitem2qimage(plt):
    sourceRect = plt.sceneBoundingRect()
    print('sourceRect: ', sourceRect)
    targetRect = plt.mapRectToDevice(sourceRect)
    print('targetRect:', targetRect)
    scene = plt.scene()
    print( 'scene: ', type(scene) )
    bgbrush =  scene.views()[0].backgroundBrush()
    bg = bgbrush.color()
    w = int( targetRect.width() )
    h = int( targetRect.height() )
    print('qimg:', w, h)
    img = QtGui.QImage(w, h, QtGui.QImage.Format_RGB32)
    img.fill(bg)
    painter = QtGui.QPainter(img)
    scene.render(painter, QtCore.QRectF(targetRect), QtCore.QRectF(sourceRect))
    painter.end()
    return img
# end

class Window(pg.GraphicsLayoutWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry( PX, PY, WIDTH, HEIGHT)
        self.setBackground(WHITE)
        pg.setConfigOptions(antialias=True)
        self.draw_rect()
# end

    def draw_rect(self):
        plt = self.addPlot()
        pen_black = pg.mkPen(BLACK, width=2)
        brush_cyan = pg.mkBrush(CYAN)
        rect = QtWidgets.QGraphicsRectItem(0, 0, 1, 1)
        rect.setPen( pen_black)
        rect.setBrush(brush_cyan)
        plt.addItem(rect)
        qimage = plotitem2qimage(plt)
        qimage.save(OUTFILE)
# end

  
# main
app = pg.mkQApp()
win = Window()
win.show()
sys.exit(app.exec())

