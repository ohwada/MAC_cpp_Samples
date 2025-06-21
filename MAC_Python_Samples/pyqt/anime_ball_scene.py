# Python: # Python: nimate   Bouncing  Ball using QGraphicsScene
# 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from pos import *
import sys

# Window
WIN_TITLE =  "PyQt5 Bouncing  Ball  using QGraphicsScene"
PX=50
PY=50

# Anim
UPDATE_INTERVAL = 50 # msec


class Window(QGraphicsView):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.initView()
        self.startAnim()
# end

    def initView(self):
        pen = QPen(QColor(Qt.blue))
        self.pixmap_item = QGraphicsPixmapItem(QPixmap(FPATH_IMG))
        view = QGraphicsView()
        scene = QGraphicsScene()
        scene.addRect(RECT_LEFT, RECT_TOP, RECT_WIDTH, RECT_HEIGHT, pen)
        scene.addItem(self.pixmap_item)
        self.setScene(scene)
        self.pos = Pos()
# end

    def startAnim(self):
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
