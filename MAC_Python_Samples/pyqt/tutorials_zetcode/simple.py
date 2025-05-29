# simple window in PyQt5.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/firstprograms/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel


# Window
WIN_TITLE="PyQt5 Simple"
PX=50
PY=50
WIDTH= 250
HEIGHT= 150

# QLabel
TEXT="Hello World!"


def window():
    app = QApplication(sys.argv)
    win = QWidget()
    win.setWindowTitle(WIN_TITLE)
    win.setGeometry(PX, PY, WIDTH,HEIGHT)
    label = QLabel(win)
    label.setText(TEXT)
    label.move(50, 20)
    win.show()
    sys.exit(app.exec_())
# end


if __name__ == '__main__':
    window()
# end

