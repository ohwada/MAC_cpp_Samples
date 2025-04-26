# Python: plot sin wave using pyqtgraph
# 2025-04-10  K.OHWADA

# https://python.diandian.online/python-pyqtgraph-draw-sin-wave/

import numpy as np
import sys
from PyQt5.QtWidgets import QApplication, QWidget
import pyqtgraph as pg


WIN_TITLE = "sine Wave"

FREQ = 1    # sine wave frequency [Hz]
TS = 0.001  # sampling period [sec]
NS = 1000   # sampling points [pieces]

LEFT = 'left'
BOTTOM ='bottom'

TEXT_LEFT = 'Amplitude'
TEXT_BOTTOM =  'Time [sec]'

PEN_WIDTH=10

YELOW = (255,255,0)

class GuiWindow(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle(WIN_TITLE)
        self.crete_sine_wave()
        self.draw_graph()
# end

    def crete_sine_wave(self):
        self.freq = FREQ     #  sine wave frequency 
        self.Ts = TS  # ampling period
        self.Ns = NS # sampling points
        self.ns = np.arange(0, self.Ns)  # sample number
        self.time = self.ns * self.Ts
        self.sin = np.sin(2 * np.pi * self.freq * (self.ns * self.Ts))  # ? 1
# end

    def draw_graph(self):                                            # ? 2
        self.graph = pg.GraphicsLayoutWidget(show=True)
        self.p0 = self.graph.addPlot()
        self.p0.setLabel(LEFT,  TEXT_LEFT )
        self.p0.setLabel(BOTTOM, TEXT_BOTTOM)
        self.p0.plot(x=self.time, y=self.sin, pen=pg.mkPen(YELOW, width=PEN_WIDTH))
# end

if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = GuiWindow()
    sys.exit(app.exec())
# end
