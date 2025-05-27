# Python: show Image with QPixmap
# 2025-04-10  K.OHWADA

#  https://www.tutorialspoint.com/pyqt5/pyqt5_qpixmap_class.htm

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


# Window
WIN_TITLE ="PyQt5 QPixmap Demo"
PX=50
PY=50
WIDTH= 300
HEIGHT= 200

FPATH_IMG = "python_logo.png"


def window():
    win = QWidget()
    win.setWindowTitle(WIN_TITLE)
    win.setGeometry(PX, PY, WIDTH,HEIGHT)
    l1 = QLabel()
    l1.setPixmap(QPixmap(FPATH_IMG))
    vbox = QVBoxLayout()
    vbox.addWidget(l1)
    win.setLayout(vbox)
    return win
# end

def main():
    app = QApplication(sys.argv)
    win = window()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
   main()
# end