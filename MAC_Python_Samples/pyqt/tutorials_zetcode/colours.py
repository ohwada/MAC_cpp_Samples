#  This example draws three rectangles in three different colours.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/painting/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import QWidget, QApplication
from PyQt5.QtGui import QPainter, QColor, QBrush, QImage
from PyQt5.QtCore import Qt
import sys


# Window
WIN_TITLE = "PyQt5 Colours"
PX=50
PY=50
WIDTH= 350
HEIGHT= 100

# QColor
COLOR1 = QColor(0, 0, 0) # black

COLOR2 = QColor(200, 0, 0) # red
    
COLOR3 = QColor(255, 80, 0, 160) # orange

COLOR4 = QColor(25, 0, 90, 200) # indigo

Named_Color = "#d4d4d4"

# QImage
OUTFILE = "qt_tutorials_zetcode_draw_colors.png"


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
        self.drawPaint(self)
# end

    def drawPaint(self, device):
        qp = QPainter()
        qp.begin(device)
        self.drawRectangles(qp)
        qp.end()
# end

    def drawRectangles(self, qp):
        col =  COLOR1
        col.setNamedColor(Named_Color)
        qp.setPen(col)
        qp.setBrush(COLOR2)
        qp.drawRect(10, 15, 90, 60)
        qp.setBrush(COLOR3)
        qp.drawRect(130, 15, 90, 60)
        qp.setBrush(COLOR4)
        qp.drawRect(250, 15, 90, 60)
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