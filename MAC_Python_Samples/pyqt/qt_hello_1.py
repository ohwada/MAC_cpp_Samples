# Python: display Qt window
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


def window():
    app = QApplication(sys.argv)
    w = QWidget()
    b = QLabel(w)
    b.setText(TEXT)
    w.setGeometry(PX, PY, WIDTH,HEIGHT)
    b.move(BX, BY)
    w.setWindowTitle(TITLE)
    w.show()
    sys.exit(app.exec_())
# end

# main
window()


