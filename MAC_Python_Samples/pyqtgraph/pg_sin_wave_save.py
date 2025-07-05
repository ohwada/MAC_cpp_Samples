# Python: plot sin wave using pyqtgraph
# 2025-04-10  K.OHWADA

# https://python.diandian.online/python-pyqtgraph-draw-sin-wave/


from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import pyqtgraph.exporters
import numpy as np
import sys


WIN_TITLE = "Sin Wave"
PX=50
PY=50
WIDTH=500
HEIGHT=500

OUTFILE = "pg_sin_wave.png"

# Plot
PLT_TITLE = "Sin Wave"

FREQ = 1    # sine wave frequency [Hz]
TS = 0.001  # sampling period [sec]
NS = 1000   # sampling points [pieces]

LEFT = 'left'
BOTTOM ='bottom'

TEXT_LEFT = 'Amplitude'
TEXT_BOTTOM =  'Time [sec]'

PEN_WIDTH=5

YELOW = (255,255,0)



class Window(pg.LayoutWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.initView()
# end

    def initView(self):
        graph = pg.GraphicsLayoutWidget(show=True)
        self.addWidget(graph) 
        plt = graph.addPlot()
        self.draw_plot(plt)
        self.save_plot(plt)
# end

    def draw_plot(self, plt):
        pen_yellow = pg.mkPen(YELOW, width=PEN_WIDTH)
        ns = np.arange(0, NS)
        time = ns * TS
        sin = np.sin(2 * np.pi * FREQ * (time) ) 
        plt_title = '<font size=\'4\' color=\'#FFFFFF\'>' + PLT_TITLE +'</font>'
        plt.setTitle(plt_title)                                      
        plt.setLabel(LEFT,  TEXT_LEFT )
        plt.setLabel(BOTTOM, TEXT_BOTTOM)
        plt.plot(x=time, y=sin, pen=pen_yellow) 
# end

    def save_plot(self, plt):
        exporter = pg.exporters.ImageExporter(plt) 
        exporter.export(OUTFILE) 
# end


def main():
    app = pg.mkQApp()
    win = Window()
    win.show()
    sys.exit(app.exec())
# end


if __name__ == '__main__':
    main()
# end
