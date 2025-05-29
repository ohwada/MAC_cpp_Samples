# This program creates a menubar. 
# The menubar has one menu with an exit action.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/menustoolbars/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import QMainWindow, QAction, qApp, QApplication
from PyQt5.QtGui import QIcon


# Window
WIN_TITLE ="PyQt5 Simple Menu"
PX=50
PY=50
WIDTH= 300
HEIGHT= 200

# Menu
MENU_EXIT =  "&Exit"
MENU_FILE = "&File"
CTRL_Q = "Ctrl+Q"

EXIT_STATUSTIP = "Exit application"

FPATH_EXIT_ICON = "exit.png"


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        exitAct = QAction(QIcon(FPATH_EXIT_ICON), MENU_EXIT, self)
        exitAct.setShortcut(CTRL_Q)
        exitAct.setStatusTip(EXIT_STATUSTIP)
        exitAct.triggered.connect(qApp.quit)
        self.statusBar()
        menubar = self.menuBar()

# Missing menuBar in PyQt5
# https://stackoverflow.com/questions/39574105/missing-menubar-in-pyqt5
        menubar.setNativeMenuBar(False)

        fileMenu = menubar.addMenu(MENU_FILE)
        fileMenu.addAction(exitAct)
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