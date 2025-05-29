#  This program draws a Bézier curve with QPainterPath.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/painting/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtGui import QPainter, QPainterPath, QPen, QImage
from PyQt5.QtWidgets import QWidget, QApplication
from PyQt5.QtCore import Qt, QPointF


# Window
WIN_TITLE = "PyQt5 Bézier Curve"
PX=50
PY=50
WIDTH= 400
HEIGHT= 250

# QPen
PEN_WIDTH = 2

# QImage
OUTFILE = "qt_tutorials_zetcode_bezier_curve.png"


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
        print('paintEven')
        img = QImage(self.size(), QImage.Format_RGB32)
        img.fill(Qt.white)
        self.drawPaint(img)
        img.save(OUTFILE)
        self. drawPaint(self)

    def drawPaint(self, device):
        qp = QPainter()
        qp.begin(device)
        qp.setRenderHint(QPainter.Antialiasing)
        self.drawBezierCurve(qp)
        qp.end()
# end

    def drawBezierCurve(self, qp):
        print('drawBezierCurve')
        c1_point = QPointF(30, 30)
        c2_point = QPointF(200, 350)
        end_point = QPointF(350, 30)
        path = QPainterPath()
        path.moveTo(c1_point)
        path.cubicTo(c1_point, c2_point, end_point)
        pen = QPen(Qt.blue)    
        pen.setWidth(PEN_WIDTH)
        qp.setPen(pen)
        qp.drawPath(path)
# end


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
    main()# end
