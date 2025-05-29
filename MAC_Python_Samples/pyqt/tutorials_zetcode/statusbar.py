# This program creates a statusbar.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/menustoolbars/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import QMainWindow, QApplication


# Window
WIN_TITLE ="PyQt5 Statusbar"
PX=50
PY=50
WIDTH= 250
HEIGHT= 150

# StatusBar
STATUSBAR_MESSAGE = "Ready"

class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        self.statusBar().showMessage(STATUSBAR_MESSAGE)
# end


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
    main()
# end
