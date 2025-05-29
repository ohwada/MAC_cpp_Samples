#  we draw 6 lines using different pen styles.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/painting/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import QWidget, QApplication
from PyQt5.QtGui import QPainter, QPen, QImage
from PyQt5.QtCore import Qt
import sys


# Window
WIN_TITLE = "PyQt5 Pen Styles"
PX=50
PY=50
WIDTH= 300
HEIGHT= 300

# QImage
OUTFILE = "qt_tutorials_zetcode_pens.png"



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
        img = QImage(self.size(), QImage.Format_RGB32)
        img.fill(Qt.white)
        self.drawPaint(img)
        img.save(OUTFILE)
        self. drawPaint(self)
# end

    def drawPaint(self, device):
        qp = QPainter()
        qp.begin(device)
        self.drawLines(qp)
        qp.end()
# end

    def drawLines(self, qp):
        print('drawLines')
        pen = QPen(Qt.black, 2, Qt.SolidLine)
        qp.setPen(pen)
        qp.drawLine(20, 40, 250, 40)
        pen.setStyle(Qt.DashLine)
        qp.setPen(pen)
        qp.drawLine(20, 80, 250, 80)
        pen.setStyle(Qt.DashDotLine)
        qp.setPen(pen)
        qp.drawLine(20, 120, 250, 120)
        pen.setStyle(Qt.DotLine)
        qp.setPen(pen)
        qp.drawLine(20, 160, 250, 160)
        pen.setStyle(Qt.DashDotDotLine)
        qp.setPen(pen)
        qp.drawLine(20, 200, 250, 200)
        pen.setStyle(Qt.CustomDashLine)
        pen.setDashPattern([1, 4, 5, 4])
        qp.setPen(pen)
        qp.drawLine(20, 240, 250, 240)
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