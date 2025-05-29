# This example shows an icon in the titlebar of the window.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/firstprograms/
# modify: 2025-04-10  K.OHWADA

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import sys

# Window
WIN_TITLE="PyQt5 Icon"
PX=50
PY=50
WIDTH= 300
HEIGHT= 200

# Icon
FPATH_ICON  = "python_icon.png"


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        self.setWindowTitle(WIN_TITLE)

# On macOS, window icons represent the active document, 
# and will not be displayed unless a file path has also been set using setWindowFilePath .
        icon = QIcon(FPATH_ICON)
        self.setWindowIcon(icon)
        self.setWindowFilePath(FPATH_ICON)
# end


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec_())
# rnd

if __name__ == '__main__':
    main()
# end
