# Python: # Python: nimate   Bouncing  Ball using QGraphicsScene
# 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from pos import Pos
from ball import *
import sys

# Window
WIN_TITLE =  "PyQt5 Bouncing  Ball  using QGraphicsScene"
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



class Window(QGraphicsView):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.initView()
        self.startAnim()
# end

    def initView(self):
        pen_blue = QPen(QColor(Qt.blue), 1)
        self.pixmap_item = QGraphicsPixmapItem(QPixmap(FPATH_IMG))
        view = QGraphicsView()
        scene = QGraphicsScene()
        rect = QRectF(RECT)
        scene.addRect(rect, pen_blue)
        scene.addItem(self.pixmap_item)
        self.setScene(scene)
# end

    def startAnim(self):
        self.pos = Pos()
        self.pos.set_range(X_MIN, X_MAX, Y_MIN, Y_MAX)
        self.pos.set_init(X_INIT, Y_INIT, VX_INIT, VY_INIT)
        timer = QTimer(self)
        timer.timeout.connect(self.updatePos)
        timer.start(UPDATE_INTERVAL) 
# end

    def updatePos(self):
        x, y =  self.pos.update_pos()
        self.pixmap_item.setPos( QPointF(x, y) )
# end


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec())
# end

if __name__ == '__main__':
    main()
# end
