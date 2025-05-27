# Python: display Qt window
# the object oriented solution of qt_hell.py
# 2025-04-10  K.OHWADA

#  https://www.tutorialspoint.com/pyqt5/pyqt5_hello_world.htm

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


# Window
WIN_TITLE="PyQt5"
PX=50
PY=50
WIDTH=200
HEIGHT=50

# Label
TEXT="Hello World!"

# Font
FONT_FAMILY = "Arial"
FONT_SIZE = 16


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.setWindowTitle(WIN_TITLE)
        print(  self.rect() )
        self.setGeometry(PX, PY, WIDTH, HEIGHT)

        self.label = QLabel(self)
        self.label.setText(TEXT)
        font = QFont()
        font.setFamily(FONT_FAMILY)
        font.setPointSize(  FONT_SIZE)
        self.label.setFont(font)
        self.label.move(50, 20)
# end

def main():
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())
# end

# main
main()
