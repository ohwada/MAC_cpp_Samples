# Python: animate   Bouncing  Ball
# 2025-04-10  K.OHWADA



from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import sys

# Window
WIN_TITLE = "PyQt5  Bouncing  Ball"
PX = 10
PY = 10
WIDTH = 480
HEIGHT = 360

# Ball
FPATH_IMG = "soccer_ball.png"

BALL_SIZE = 32

# Pos
MIN_X = int(0.2 * WIDTH)
LEFT_X = int(0.9 * WIDTH)
MAX_X = LEFT_X - BALL_SIZE

MIN_Y = int(0.1 * HEIGHT)
BOTTOM_Y= int(0.9 * HEIGHT)
MAX_Y = BOTTOM_Y - BALL_SIZE

INIT_X = MIN_X
INIT_Y = MIN_Y 
V_X = 2 # velocity x
V_Y = 3 # velocity y

BALL_E = 0.75 # the coefficient of repulsion
BALL_DT = 0.2 # Distance travelled by the ball

# Rect
RECT_LEFT = MIN_X
RECT_TOP = MIN_Y
RECT_WIDTH = LEFT_X - MIN_X
RECT_HEIGHT =  BOTTOM_Y - MIN_Y

# Anim
UPDATE_INTERVAL = 10 # msec


# calc Ball position
# https://qiita.com/MENDY/items/e1b432df1e0bfe8b680c
class Pos():
    def __init__(self):
        self.x = INIT_X
        self.y = INIT_Y
        self.v_x = V_X
        self.v_y = V_Y
# end

    def update_pos(self):
        self.x += self.v_x * BALL_DT
        self.y += self.v_y * BALL_DT
    #x limit
        if self.x > MAX_X:
            self.x = MAX_X
            self.update_velocity_x()
        elif self.x < MIN_X:
            self.x = MIN_X
            self.update_velocity_x()
# end
# y limit
        if self.y > MAX_Y:
            self.y = MAX_Y
            self.update_velocity_y()
        elif self.y < MIN_Y:
            self.y = MIN_Y
            self.update_velocity_y()
# end
        return self.x, self.y
# end

    def update_velocity_x(self):
        self.v_x = - BALL_E * self.v_x
    # end

    def update_velocity_y(self):
        self.v_y = - BALL_E * self.v_y
# end


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
