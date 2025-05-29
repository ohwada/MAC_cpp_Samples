# we display an image on the window.
# Author: Jan Bodnar
# https://zetcode.com/pyqt6/widgets2/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import (QWidget, QHBoxLayout,
        QLabel, QApplication)
from PyQt5.QtGui import QPixmap
import sys


# Window
WIN_TITLE="PyQt5 Sid"
PX=50
PY=50
WIDTH= 480
HEIGHT= 360

# QPixmap
FPATH_IMG = "sid.jpg"


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        hbox = QHBoxLayout(self)
        pixmap = QPixmap(FPATH_IMG)
        lbl = QLabel(self)
        lbl.setPixmap(pixmap)
        hbox.addWidget(lbl)
        self.setLayout(hbox)
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

