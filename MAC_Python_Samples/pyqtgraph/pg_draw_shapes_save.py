# Python: draw Shapes using PlotItem
# save file using PlotItem or exporters
# 2025-04-10  K.OHWADA


import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtWidgets, QtGui
import pyqtgraph.exporters as  exporters
import numpy as np
import math
import sys, os


WIN_TITLE = "draw Shapes"
PX = 10
PY = 10
WIDTH = 480
HEIGHT = 360

BOTTOM = "bottom"
LEFT =  "left"

TEXT = "Hello Python"
FONT = 'Arial'
FONT_SIZE = 20

CX = 320
CY =160

LENGTH_OUT = 70
LENGTH_IN = 30

RAD = math.pi/5
RAD_START = math.pi/2

OUTFILE = "pg_draw_shapes.png"

OUTFILE_EXPORTERS = "pg_draw_shapes_exporters.png"

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE =  (0, 0, 255)
CYAN = (0, 255, 255)
PINK = (255, 192, 192)


class Window(pg.GraphicsLayoutWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry( PX, PY, WIDTH, HEIGHT)
        self.setBackground(WHITE)
        pg.setConfigOptions(antialias=True)
        self.draw_shapes()
# end


    def init_Plot(self):
        plt = self.addPlot()
        plt.setRange(xRange = (0, WIDTH), yRange = (0,  HEIGHT))
        plt.showAxis(BOTTOM, False)
        plt.showAxis(LEFT, False)
        return plt
# end


    def draw_shapes(self):
        plt= self.init_Plot()
        pen_black = pg.mkPen(BLACK, width=1)
        pen_blue = pg.mkPen(BLUE, width=2)
        pen_green = pg.mkPen(GREEN, width=2)
        brash_green = pg.mkBrush(GREEN)
        brash_cyan = pg.mkBrush(CYAN)
        rect0 = QtWidgets.QGraphicsRectItem(QtCore.QRectF(0, 0, WIDTH, HEIGHT))
        rect0.setPen( pen_black)
        plt.addItem(rect0)
        font =  QtGui.QFont(FONT, FONT_SIZE)
        text = pg.TextItem(TEXT)
        text.setFont(font)
        text.setColor(RED)
        text.setPos(40, 340)
        plt.addItem(text)
        line = QtWidgets.QGraphicsLineItem(40, 260, 200, 260)
        line.setPen( pen_blue)
        plt.addItem(line)
        rect1 = QtWidgets.QGraphicsRectItem(QtCore.QRectF(40,150,150,100))
        rect1.setPen( pen_blue)
        plt.addItem(rect1)
        rect2 = QtWidgets.QGraphicsRectItem(QtCore.QRectF(50,160,120,60))
        rect2.setPen(pen_black)
        rect2.setBrush( brash_green)
        plt.addItem(rect2)
        ellipse = QtWidgets.QGraphicsEllipseItem(220,200,70,100)
        ellipse.setPen(pen_black)
        ellipse.setBrush( brash_cyan)
        plt.addItem(ellipse)
        arrow1 = pg.ArrowItem(angle=70, headLen=30, tailLen=50, tailWidth=20, pen=pen_black, brush= brash_green)
        arrow1.setPos(70, 120)
        plt.addItem(arrow1)
        arrow2 = pg.ArrowItem(angle=100, headLen=30, tailLen=30, tailWidth=30, pen=pen_black, brush= brash_cyan)
        arrow2.setPos(170, 100)
        plt.addItem(arrow2)
        self.draw_pentagram(plt)
        self.save_plot(plt)
# end

    def draw_pentagram(self, plt):
        pen_black = pg.mkPen(BLACK, width=1)
        brush_pink = pg.mkBrush(PINK)
        points = []
        for i in range(10):
            rad = (RAD*i) +RAD_START
            radius =  LENGTH_OUT if (i%2 ==0) else LENGTH_IN
            x = radius * math.cos(rad) + CX
            y = radius *math.sin(rad) + CY
            print(x,y)
            points.append ( QtCore.QPointF(x, y) )
# end
        polygon = QtGui.QPolygonF( points)
        polygon_item = QtWidgets.QGraphicsPolygonItem(polygon) 
        polygon_item.setPen(pen_black)
        polygon_item.setBrush(brush_pink)
        plt.addItem(polygon_item)
# end

    def save_plot(self, plt):
        plt.writeImage(OUTFILE)
        print('create ', OUTFILE)
        # exporter = pg.exporters.ImageExporter(plt) 
        # exporter.export(OUTFILE_EXPORTERS) 
# end

# main
app = pg.mkQApp()
win = Window()
win.show()
sys.exit(app.exec())





