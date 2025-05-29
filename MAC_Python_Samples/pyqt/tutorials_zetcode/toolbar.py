# This program creates a toolbar.
# The toolbar has one action, which terminates the application, if triggered.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/menustoolbars/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import QMainWindow, QAction, qApp, QApplication
from PyQt5.QtGui import QIcon


# Window
WIN_TITLE ="PyQt5 Toolbar"
PX=50
PY=50
WIDTH= 300
HEIGHT= 200

# Menu
EXIT =  "Exit"
CTRL_Q = "Ctrl+Q"

FPATH_EXIT_ICON = "exit.png"


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        exitAct = QAction(QIcon(FPATH_EXIT_ICON), EXIT, self)
        exitAct.setShortcut(CTRL_Q)
        exitAct.triggered.connect(qApp.quit)
        self.toolbar = self.addToolBar( EXIT)
        self.toolbar.addAction(exitAct)
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
