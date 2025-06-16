# Python: animate along curve using
# 2025-04-10  K.OHWADA

# https://zetcode.com/pyqt/qpropertyanimation/


from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
import sys


# Window
WIN_TITLE =  "PyQt5 Animation along curve"
PX=50
PY=50
WIDTH = 480
HEIGHT = 360

# QPainterPath
START_X = 30
START_Y = 30

CURVE_X = 200
CURVE_Y = 350

END_X = 350
END_Y = 30

FPATH_IMG = "soccer_ball.png"

# Anime
DURATION = 10000 # 10 sec

NUM = 100
MAX_NUM = 101


class Ball(QLabel):
    def __init__(self, parent):
        super().__init__(parent)
        pix = QPixmap(FPATH_IMG)
        self.h = pix.height()
        self.w = pix.width()
        self.setPixmap(pix)
# end

    def _set_pos(self, pos):
        self.move(pos.x() - self.w//2, pos.y() - self.h//2)
# end

    pos = pyqtProperty(QPoint, fset=_set_pos)
# end


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.initView()
        self.startAnim()
# end

    def initView(self):
        self.path = QPainterPath()
        self.path.moveTo(START_X, START_Y)
        self.path.cubicTo(START_X, START_Y, CURVE_X, CURVE_Y, END_X, END_Y)
        self.ball = Ball(self)
        self.ball.pos = QPoint(START_X, START_Y)
# end

    def paintEvent(self, e):
        qp = QPainter()
        qp.begin(self)
        qp.setRenderHint(QPainter.RenderHint.Antialiasing)
        qp.drawPath(self.path)
        qp.end()
# end

    def startAnim(self):
        self.anim = QPropertyAnimation(self.ball, b'pos')
        self.anim.setStartValue(QPoint(START_X, START_Y))
        vals = [(p/NUM) for p in range(0, MAX_NUM)]
        for i in vals:
            self.anim.setKeyValueAt(i, self.path.pointAtPercent(i))
# end
        self.anim.setEndValue(QPoint(END_X, END_Y))
        self.anim.setDuration(DURATION)
        self.anim.start()
# end

def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec())


if __name__ == '__main__':
    main()

