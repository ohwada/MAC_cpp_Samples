#  draw randomly 1000 red points on the window.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/painting/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import QWidget, QApplication
from PyQt5.QtGui import QPainter, QPen, QImage
from PyQt5.QtCore import Qt
import sys, random


# Window
WIN_TITLE = "PyQt5 Points"
PX=50
PY=50
WIDTH= 300
HEIGHT= 200

MAX_POINTS = 1000

# QPen
PEN_WIDTH = 2

# QImage
OUTFILE = "qt_tutorials_zetcode_draw_point.png"


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
# end

    def paintEvent(self, e):
        print('paintEvent')
        img = QImage(self.size(), QImage.Format_RGB32)
        img.fill(Qt.white)
        self.drawPaint(img)
        img.save(OUTFILE)
        self.drawPaint(self)
# end

    def drawPaint(self, device):
        qp = QPainter()
        qp.begin(device)
        self.drawPoints(qp)
        qp.end()
# end

    def drawPoints(self, qp):
        pen = QPen(Qt.red)    
        pen.setWidth(PEN_WIDTH)
        qp.setPen(pen)
        size = self.size()
        if ( size.width() <=  PEN_WIDTH) or ( size.height() <= PEN_WIDTH):
            return
# end
        for i in range(MAX_POINTS):
            x = random.randint(PEN_WIDTH, size.width() - PEN_WIDTH)
            y = random.randint(PEN_WIDTH, size.height() - PEN_WIDTH)
            # print(x, y)
            qp.drawPoint(x, y)
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