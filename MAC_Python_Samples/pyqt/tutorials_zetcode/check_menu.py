# This program creates a checkable menu.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/menustoolbars/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import QMainWindow, QAction, QApplication


# Window
WIN_TITLE ="PyQt5 Check Menu"
PX=50
PY=50
WIDTH= 300
HEIGHT= 200

# Menu
VIEW = "View"

VIEW_STAT_ACTION = "View statusbar"

VIEW_STAT_STATUSTIP = "View statusbar"

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
        self.statusbar = self.statusBar()
        self.statusbar.showMessage(STATUSBAR_MESSAGE)
        menubar = self.menuBar()

# Missing menuBar in PyQt5
# https://stackoverflow.com/questions/39574105/missing-menubar-in-pyqt5
        menubar.setNativeMenuBar(False)

        viewMenu = menubar.addMenu(VIEW)
        viewStatAct = QAction(VIEW_STAT_ACTION, self, checkable=True)
        viewStatAct.setStatusTip(VIEW_STAT_STATUSTIP)
        viewStatAct.setChecked(True)
        viewStatAct.triggered.connect(self.toggleMenu)
        viewMenu.addAction(viewStatAct)
# end

    def toggleMenu(self, state):
        if state:
            print('show')
            self.statusbar.show()
        else:
            print('hide')
            self.statusbar.hide()
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



