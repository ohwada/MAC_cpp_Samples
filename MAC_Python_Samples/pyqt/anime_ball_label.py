# Python: nimate   Bouncing  Ball using QLabel
# 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from pos import *
import sys


# Window
WIN_TITLE =  "  Bouncing  Ball using QLabel"
PX=50
PY=50

# Anim
UPDATE_INTERVAL = 50 # msec


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
        self.label.setGeometry(INIT_X, INIT_Y, BALL_SIZE, BALL_SIZE)
        self.label.setPixmap(pixmap)
        self.pos = Pos()
# end

    def paintEvent(self, e):
        qp = QPainter()
        qp.begin(self)
        qp.setPen(QColor(Qt.blue))
        qp.drawRect(RECT_LEFT, RECT_TOP, RECT_WIDTH, RECT_HEIGHT)
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

