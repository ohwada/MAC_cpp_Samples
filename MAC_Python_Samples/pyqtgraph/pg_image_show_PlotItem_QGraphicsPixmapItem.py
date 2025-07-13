# Python: load Image file using QPixmap
# show Image using PlotIrem and QGraphicsPixmapItem
# It will be displayed upside down
# If you set invertY, 
# it will be displayed in the correct orientation
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


WIN_TITLE = "draw Shapes"
PX = 10
PY = 10
WIDTH = 480
HEIGHT = 360

BOTTOM = "bottom"
LEFT =  "left"

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)

USAGE_FORMAT = "Usage: python {:s}  <image filepath> [invertY] [resize]"


def resize_pixmap(img):
    iw = img.width()
    ih = img.height()
    print('original: ', iw, ih)
    if(iw==0) or (ih==0):
        return None
    ratio_w = WIDTH/iw
    ratio_h = HEIGHT/ih
    ratio = min(ratio_w, ratio_h)
    if (iw> WIDTH) or (ih > HEIGHT):
        w = int(ratio * iw)
        h = int(ratio * ih)
        print('resize: ', w, h)
        img = img.scaled(w, h)
# end
    return img
# end

class Window(pg.GraphicsLayoutWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry( PX, PY, WIDTH, HEIGHT)
        self.setBackground(WHITE)
        pg.setConfigOptions(antialias=True)
# end

    def set_pixmap(self, pixmap, is_inverty):
        brush_red = pg.mkBrush(RED)
        plt = self.addPlot()
        # plt.showAxis(BOTTOM, False)
        # plt.showAxis(LEFT, False)
        if is_inverty:
            print('invertY')
            plt.invertY(True)
# end
        pixmap_item = QtWidgets.QGraphicsPixmapItem(pixmap)
        pixmap_item.setPos(10, 10)
        plt.addItem(pixmap_item)
        rect = QtWidgets.QGraphicsRectItem(QtCore.QRectF(10,10,5,5))
        rect.setBrush(brush_red)
        plt.addItem(rect)
# end

    def set_fpath(self, fpath, is_inverty, is_resize):
        basename= os.path.basename(fpath)
        self.setWindowTitle(basename)
        pixmap = QtGui.QPixmap(fpath)
        if is_resize:
            pixmap =  resize_pixmap(pixmap)
# end
        self.set_pixmap(pixmap, is_inverty)
# end

  
def main(fpath, is_inverty, is_resize):
    app = pg.mkQApp()
    win = Window()
    win.set_fpath(fpath, is_inverty, is_resize)
    win.show()
    sys.exit(app.exec())
# end


def usage(script):
    usage = USAGE_FORMAT.format(script)
    print(usage)
# end


# main
fpath = ""
is_inverty = False
is_resize = False
args = sys.argv
argc = len(args)
if argc < 2:
    usage(args[0])
    exit()
elif argc >= 4:
    fpath = args[1]
    is_inverty = int(args[2])
    is_resize = int(args[3])
elif argc >= 3:
    fpath = args[1]
    is_inverty = int(args[2])
elif argc >= 2:
    fpath = args[1]
# end
main(fpath, is_inverty, is_resize)




