# Python: animate Ball object with QPropertyAnimation in a Graphics View Framework
# 2025-04-10  K.OHWADA

# https://zetcode.com/pyqt/qpropertyanimation/


from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
import sys

# Window
WIN_TITLE =  "PyQt5 Ball animation"
PX=50
PY=50
WIDTH = 480
HEIGHT = 360

# QGraphicsScene
SCENE_LEFT = 0
SCENE_TOP = 0
SCENE_WIDTH = 300
SCENE_HEIGHT = 300

 # Ball
FPATH_IMG = "soccer_ball.png"

# Anim
START_X = 5
START_Y = 30
X1 = 80
Y1 = 30
X2 = 200
Y2 = 30
X3 = 250
Y3 = 250
END_X = 290
END_Y =30

DURATION = 100000 # 10 sec


class Ball(QObject):
    def __init__(self):
        super().__init__()
        self.pixmap_item = QGraphicsPixmapItem(QPixmap(FPATH_IMG))
# end

    def _set_pos(self, pos):
        self.pixmap_item.setPos(pos)
# end

    pos = pyqtProperty(QPointF, fset=_set_pos)
# end


class Window(QGraphicsView):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.initView()
        self.startAnim()
# end

    def initView(self):
        self.setRenderHint(QPainter.RenderHint.Antialiasing)
        self.ball = Ball()
        self.scene = QGraphicsScene(self)
        self.scene.setSceneRect(SCENE_LEFT, SCENE_TOP, SCENE_WIDTH, SCENE_HEIGHT)
        self.scene.addItem(self.ball.pixmap_item)
        self.setScene(self.scene)
# end

    def startAnim(self):
        self.anim = QPropertyAnimation(self.ball, b'pos')
        self.anim.setStartValue(QPointF( START_X, START_Y))
        self.anim.setKeyValueAt(0.3, QPointF(X1 , Y1))
        self.anim.setKeyValueAt(0.5, QPointF(X2, Y2))
        self.anim.setKeyValueAt(0.8, QPointF(X3, Y3))
        self.anim.setEndValue(QPointF(END_X, END_Y))
        self.anim.setDuration(DURATION)
        self.anim.start()
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
