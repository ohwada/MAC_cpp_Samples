# Python: display Qt window
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


def window():
    app = QApplication(sys.argv)
    win = QWidget()
    win.setWindowTitle(WIN_TITLE)
    print(  win.rect() )
    win.setGeometry(PX, PY, WIDTH,HEIGHT)

    l = QLabel(win)
    l.setText(TEXT)
    l.move(50, 20)
    
    win.show()
    sys.exit(app.exec_())
# end

# main
window()


