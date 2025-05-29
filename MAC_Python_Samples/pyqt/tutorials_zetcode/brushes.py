#  This example draws nine rectangles in different brush styles.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/painting/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import QWidget, QApplication
from PyQt5.QtGui import QPainter, QBrush, QImage
from PyQt5.QtCore import Qt
import sys


# Window
WIN_TITLE = "PyQt5 Brushes"
PX=50
PY=50
WIDTH= 400
HEIGHT= 300

# QImage
OUTFILE = "qt_tutorials_zetcode_burashs.png"


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
        self. drawPaint(self)
# end


    def drawPaint(self, device):
        qp = QPainter()
        qp.begin(device)
        self.drawBrushes(qp)
        qp.end()
# end

    def drawBrushes(self, qp):
        print('drawBrushes')
        brush = QBrush(Qt.SolidPattern)
        qp.setBrush(brush)
        qp.drawRect(10, 15, 90, 60)
        brush.setStyle(Qt.Dense1Pattern)
        qp.setBrush(brush)
        qp.drawRect(130, 15, 90, 60)
        brush.setStyle(Qt.Dense2Pattern)
        qp.setBrush(brush)
        qp.drawRect(250, 15, 90, 60)
        brush.setStyle(Qt.DiagCrossPattern)
        qp.setBrush(brush)
        qp.drawRect(10, 105, 90, 60)
        brush.setStyle(Qt.Dense5Pattern)
        qp.setBrush(brush)
        qp.drawRect(130, 105, 90, 60)
        brush.setStyle(Qt.Dense6Pattern)
        qp.setBrush(brush)
        qp.drawRect(250, 105, 90, 60)
        brush.setStyle(Qt.HorPattern)
        qp.setBrush(brush)
        qp.drawRect(10, 195, 90, 60)
        brush.setStyle(Qt.VerPattern)
        qp.setBrush(brush)
        qp.drawRect(130, 195, 90, 60)
        brush.setStyle(Qt.BDiagPattern)
        qp.setBrush(brush)
        qp.drawRect(250, 195, 90, 60)
# end


def main():
    app = QApplication(sys.argv)
    win =  Window()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
    main()
# end



