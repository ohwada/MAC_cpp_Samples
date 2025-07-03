# Python: nimate   Bouncing  Ball using QLabel
# 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from pos import Pos
from ball import *
import sys


# Window
WIN_TITLE =  "  Bouncing  Ball using QLabel"
PX=50
PY=50
WIDTH = 480
HEIGHT = 360

# Anim
UPDATE_INTERVAL = 100 # msec

# ball rect
rect =  getRect(WIDTH, HEIGHT, 0.2, 0.9, 0.1, 0.9)

RECT = rect

X_MIN = rect.left()

X_MAX = rect.right() - BALL_SIZE

Y_MIN = rect.top()

Y_MAX = rect.bottom()  - BALL_SIZE

X_INIT = X_MIN

Y_INIT = Y_MIN

VX_INIT =Pos.VX

VY_INIT = Pos.VY


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.initView()
        self.startAnim()
# end

    def initView(self):
        self.label = QLabel(self)
        pixmap =  QPixmap(FPATH_IMG)
        self.label.setGeometry(X_INIT, Y_INIT, BALL_SIZE, BALL_SIZE)
        self.label.setPixmap(pixmap)
        self.pos = Pos()
        self.pos.set_range(X_MIN, X_MAX, Y_MIN, Y_MAX)
        self.pos.set_init(X_INIT, Y_INIT, VX_INIT, VY_INIT)
# end

    def paintEvent(self, e):
        qp = QPainter()
        qp.begin(self)
        qp.setPen(QColor(Qt.blue))
        qp.drawRect(RECT)
        qp.end()
# end

    def startAnim(self):
        timer = QTimer(self)
        timer.timeout.connect(self.updatePos)
        timer.start(UPDATE_INTERVAL) 
# end

    def updatePos(self):
        x, y =  self.pos.update_pos()
        self.label.move( int(x), int(y) )
# end


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec())


if __name__ == '__main__':
    main()

