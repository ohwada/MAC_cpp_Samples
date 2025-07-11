# Python: draw rectangle
# confirm the coordinate system of PlotItem
# 2025-04-10  K.OHWADA


import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtWidgets, QtGui
import sys, os


WIN_TITLE = "Coordinate System"
PX = 10
PY = 10
WIDTH = 480
HEIGHT = 360

BOTTOM = "bottom"
LEFT =  "left"


WHITE =  (255, 255, 255)
RED =  (255, 0, 0)
GREEN =  (0, 255, 0)
BLUE =  (0, 0, 255)

OUTFILE_FORMAT= "pg_draw_rect_{:d}_{:d}_{:d}.png"

USAGE_FORMAT =	 "Usage: python {:s}  [rect] [invrtY] [set Range]"


class Window(pg.GraphicsLayoutWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry( PX, PY, WIDTH, HEIGHT)
        self.setBackground(WHITE)
        pg.setConfigOptions(antialias=True)
# end

    def set_param(self, rect_num, is_inverty,  is_set_range):
        plt = self.init_Plot(is_inverty,  is_set_range)
        print('viewGeometry: ', plt.viewGeometry() )
        self.outfile = OUTFILE_FORMAT.format( rect_num, is_inverty,  is_set_range)
        self.draw_rect(plt, rect_num)
# end

    def init_Plot(self, is_inverty,  is_set_range):
        plt = self.addPlot()
        if is_set_range:
            print('set range')
            plt.setRange(xRange = (0, WIDTH), yRange = (0,  HEIGHT))
        # plt.showAxis(BOTTOM, False)
        # plt.showAxis(LEFT, False)
        if is_inverty:
            print('invertY')
            plt.invertY(True)
        return plt
# end

    def draw_rect(self, plt, rect_num):
        pen_blue = pg.mkPen(BLUE, width=2)
        pen_red = pg.mkPen(RED, width=2)
        brush_red = pg.mkBrush(RED)
        is_draw = False
        if rect_num == 1:
            rect1 = QtWidgets.QGraphicsRectItem(0, 0, 1, 1)
            rect2 = QtWidgets.QGraphicsRectItem(0, 0, 0.1, 0.1)
            is_draw = True
        elif rect_num == 2:
            rect1 = QtWidgets.QGraphicsRectItem(10, 10, 460, 340)
            rect2 = QtWidgets.QGraphicsRectItem(10, 10, 10, 10)
            is_draw = True
# end
        if is_draw:
            rect1.setPen( pen_blue)
            plt.addItem(rect1)
            rect2.setPen(pen_red)
            plt.addItem(rect2)
# end
        plt.writeImage(self.outfile)
# end

  
def main(rect_num, is_inverty, is_set_range):
    app = pg.mkQApp()
    win = Window()
    win.set_param(rect_num, is_inverty, is_set_range)
    win.show()
    sys.exit(app.exec())
# end


def usage(script):
	usage  = USAGE_FORMAT.format(script)
	print(usage)
# end


# main
rect_num = 0
is_inverty = False
is_set_range  = False
args = sys.argv
argc = len(args)
if argc < 2:
	usage( args[0])
elif argc >= 4:
    rect_num = int(args[1])
    is_inverty = int(args[2])
    is_set_range = int(args[3])
elif argc >= 3:
    rect = int(args[1])
    is_inverty = int(args[2])
elif argc >= 2:
    rect_num = int(args[1])
# end
main(rect_num, is_inverty, is_set_range)





