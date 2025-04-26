# Python: display Qt window
# the object oriented solution of qt_hello_1.py
# 2025-04-10  K.OHWADA

#  https://www.tutorialspoint.com/pyqt5/pyqt5_hello_world.htm

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


# Window
TITLE="PyQt5"
PX=100
PY=100
WIDTH=200
HEIGHT=50

# Label
TEXT="Hello World!"
BX=50
BY=20


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.setWindowTitle(TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.label = QLabel(self)
        self.label.setText(TEXT)
        self.label.move(BX, BY)
# end

def main():
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())
# end

# main
main()
