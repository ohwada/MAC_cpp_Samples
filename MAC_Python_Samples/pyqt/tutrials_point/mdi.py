# Python: PyQt Multiple Document Interface
# 2025-04-10  K.OHWADA

#  https://www.tutorialspoint.com/pyqt5/pyqt5_multiple_document_interface.htm

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


# Window
WIN_TITLE = "PyQt5 MDI Demo"
PX=50
PY=50
WIDTH=400
HEIGHT=300

# Menu
FILE = "File"
NEW = "New"
CASCADE = "cascade"
TILED = "Tiled"

 # QMdiSubWindow(
SUB_WIDTH=  200
SUB_HEIGHT= 100


class Window(QMainWindow):
    def __init__(self):
        super(Window, self).__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.count = 0
        self.mdi = QMdiArea()
        self.setCentralWidget(self.mdi)
        menubar = self.menuBar()

# Missing menuBar in PyQt5
# https://stackoverflow.com/questions/39574105/missing-menubar-in-pyqt5
        menubar.setNativeMenuBar(False)

        file =   menubar.addMenu(FILE)
        file.addAction(NEW)
        file.addAction(CASCADE)
        file.addAction(TILED)
        file.triggered[QAction].connect(self.windowAction)
# end

    def windowAction(self, q):
        print ("windowAction:", q.text())
        if q.text() == NEW:
            self.windowActionNew()
# end
        if q.text() == CASCADE:
            self.mdi.cascadeSubWindows()
# end
        if q.text() == TILED:
            self.mdi.tileSubWindows()
# if end
# def end

    def windowActionNew(self):
        print ("windowActionNew")
        self.count = self.count+1
        sub = QMdiSubWindow()
        sub.setWidget(QTextEdit())
        sub.setWindowTitle("subWindow"+str(self.count))
        sub.resize(SUB_WIDTH, SUB_HEIGHT)
        self.mdi.addSubWindow(sub)
        sub.show()
# ebnd

# class end

def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
    main()
# end