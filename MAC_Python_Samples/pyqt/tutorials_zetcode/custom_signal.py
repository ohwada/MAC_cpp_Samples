#  we show how to emit a custom signal.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/eventssignals/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtCore import pyqtSignal, QObject
from PyQt5.QtWidgets import QMainWindow, QApplication


# Window
WIN_TITLE="PyQt5 Emit Signal"
PX=50
PY=50
WIDTH= 350
HEIGHT= 250


class Communicate(QObject):
    closeApp = pyqtSignal()
# end


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        self.c = Communicate()
        self.c.closeApp.connect(self.close)
# end

    def mousePressEvent(self, event):
        print('mousePressEvent')
        self.c.closeApp.emit()
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

