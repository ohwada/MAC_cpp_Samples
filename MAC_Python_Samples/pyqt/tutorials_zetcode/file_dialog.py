# we select a file with QFileDialog 
# and display its contents in QTextEdit.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/dialogs/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import (QMainWindow, QTextEdit,
                             QAction, QFileDialog, QApplication)
from PyQt5.QtGui import QIcon
import sys, os

# from pathlib import Path


# Window
WIN_TITLE="PyQt5 File Dialog"
PX=50
PY=50
WIDTH= 300
HEIGHT= 200

# Menu
MENU_FILE =  "&File"
CTRL_O = "Ctrl+O"
OPEN = "Open"

OPEN_FILE_STATUSTIP = "Open new File"

FPATH_ICON = "open.png"

# QFileDialog
OPEN_FILE = "Open file"


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.textEdit = QTextEdit()
        self.setCentralWidget(self.textEdit)
        self.statusBar()
        openFile = QAction(QIcon(FPATH_ICON), OPEN, self)
        openFile.setShortcut(CTRL_O)
        openFile.setStatusTip(OPEN_FILE_STATUSTIP)
        openFile.triggered.connect(self.showDialog)
        menubar = self.menuBar()

# Missing menuBar in PyQt5
# https://stackoverflow.com/questions/39574105/missing-menubar-in-pyqt5
        menubar.setNativeMenuBar(False)

        fileMenu = menubar.addMenu(MENU_FILE)
        fileMenu.addAction(openFile)
# end

    def showDialog(self):

        # home_dir = str(Path.home())
        home_dir = os.environ['HOME']
        print('home_dir: ', home_dir)

        fname = QFileDialog.getOpenFileName(self, OPEN_FILE, home_dir)
        fpath = fname[0]
        print('fpath: ', fpath)
        if fpath:
            f = open(fpath, 'r')
            with f:
                data = f.read()
                self.textEdit.setText(data)
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
