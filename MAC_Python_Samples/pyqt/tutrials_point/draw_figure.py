# Python: draw figure
# 2025-04-10  K.OHWADA

#  https://www.tutorialspoint.com/pyqt5/pyqt5_drawing_api.htm

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


# Window
WIN_TITLE ="PyQt5 Draw Demo"
PX=50
PY=50
WIDTH= 400
HEIGHT= 300


# Font
FONT_FAMILY ="Arial"
FONT_SIZE = 20

TEXT=  "hello Python"

FPATH_IMG = "python_logo.png"

OUTFILE = "qt_tutorials_poit_draw_figure.png"


class Window(QWidget):
    def __init__(self):
      super(Window, self).__init__()
      self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
# end

    def paintEvent(self, event):
        self.drawPaint(self)
        img = QImage(self.size(), QImage.Format_RGB32)
        img.fill(Qt.white)
        self.drawPaint(img)
        img.save(OUTFILE)
# end

    def drawPaint(self, device):
        qp = QPainter()
        qp.begin(device)
        qp.setPen(QColor(Qt.red))
        qp.setFont(QFont(FONT_FAMILY, FONT_SIZE))
        qp.drawText(10,50, TEXT)
        qp.setPen(QColor(Qt.blue))
        qp.drawLine(10,100,100,100)
        qp.drawRect(10,150,150,100)
        qp.setPen(QColor(Qt.yellow))
        qp.drawEllipse(100,50,100,50)
        qp.drawPixmap(220,10,QPixmap(FPATH_IMG))
        qp.fillRect(20,175,130,70,QBrush(Qt.SolidPattern))
        qp.end()
# end


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
   main()
# end

