# Python: animate   Bouncing  Ball using QPainter
# 2025-04-10  K.OHWADA


from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from pos import *
import sys


# Window
WIN_TITLE = "PyQt5  Bouncing  Ball using QPainter"
PX = 10
PY = 10

# Anim
UPDATE_INTERVAL = 50 # msec


class Window(QWidget):
    def __init__(self):
        super(Window, self).__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.startAnime()
# end

    def startAnime(self):
        self.pos = Pos()
        self.img_ball = QPixmap(FPATH_IMG)
        timer = QTimer(self)
        timer.timeout.connect(self.update)
        timer.start(UPDATE_INTERVAL) 
# end

    def paintEvent(self, e):
        x, y =  self.pos.update_pos()
        qp = QPainter()
        qp.begin(self)
        qp.setPen(QColor(Qt.blue))
        qp.drawRect(RECT_LEFT, RECT_TOP, RECT_WIDTH, RECT_HEIGHT)
        qp.drawPixmap(int(x), int(y), self.img_ball)
        qp.end()
# end


def main():
   app = QApplication(sys.argv)
   win = Window()
   win.show()
   sys.exit(app.exec_())

if __name__ == '__main__':
   main()
