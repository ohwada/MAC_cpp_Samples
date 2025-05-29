# This program creates a submenu.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/menustoolbars/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import QMainWindow, QAction, QMenu, QApplication


# Window
WIN_TITLE ="PyQt5 Submenu"
PX=50
PY=50
WIDTH= 300
HEIGHT= 200

# Menu
FILE = "File"
NEW = "New"
IMPORT = "Import"

IMP_ACTION = "Import mail"


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        menubar = self.menuBar()

# Missing menuBar in PyQt5
# https://stackoverflow.com/questions/39574105/missing-menubar-in-pyqt5
        menubar.setNativeMenuBar(False)

        fileMenu = menubar.addMenu(FILE)
        impMenu = QMenu(IMPORT, self)
        impAct = QAction(IMP_ACTION, self)
        impMenu.addAction(impAct)
        newAct = QAction(NEW, self)
        fileMenu.addAction(newAct)
        fileMenu.addMenu(impMenu)
        newAct.triggered.connect(self.do_newAct)
        impAct.triggered.connect(self.do_impAct)
  # end

    def do_newAct(self):
        print("newAct")
# end

    def do_impAct(self):
        print("impAct")
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
