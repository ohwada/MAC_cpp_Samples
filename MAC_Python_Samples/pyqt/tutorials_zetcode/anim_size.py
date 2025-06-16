# Python: animate Size using QPropertyAnimation
# 2025-04-10  K.OHWADA

# https://zetcode.com/pyqt/qpropertyanimation/

from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
import sys


# Window
WIN_TITLE =  "PyQt5 anime Size"
PX=50
PY=50
WIDTH = 480
HEIGHT = 360

# Frame
FRM_X = 150
FRM_Y = 30
FRM_WIDTH = 100
FRM_HEIGHT = 100

FRM_STYLE = "QFrame {background-color: rgb(200, 255, 255); border-width: 2; border-style: solid; border-color: rgb(255, 10, 10)}"

#  Button
START  = "Start"

# Anime
START_LEFT = FRM_X
START_TOP = FRM_Y 
START_WIDTH = 100 # FRM_WIDTH
START_HEIGHT = 100 # FRM_HEIGHT

END_LEFT = FRM_X
END_TOP = FRM_Y
END_WIDTH = 200
END_HEIGHT = 200

DURATION  = 10000 # 10 sec


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.frame = QFrame(self)
        self.frame.setGeometry(FRM_X, FRM_Y, FRM_WIDTH, FRM_HEIGHT)
       # self.frame.setFrameStyle(QFrame.Shape.Panel | QFrame.Shadow.Raised)
        self.frame.setStyleSheet(FRM_STYLE)
        button = QPushButton(START, self)
        button.clicked.connect(self.doAnim)
        button.move(30, 30)
# end

    def doAnim(self):
         self.anim = QPropertyAnimation(self.frame, b"geometry")
         self.anim.setStartValue(QRect(START_LEFT, START_TOP, START_WIDTH, START_HEIGHT))
         self.anim.setEndValue(QRect(END_LEFT, END_TOP, END_WIDTH, END_HEIGHT))
         self.anim.setDuration(DURATION)
         self.anim.start()
# end

def main():
    app = QApplication([])
    win = Window()
    win.show()
    sys.exit(app.exec())
# end

if __name__ == "__main__":
    main()
# end
