# This example shows how to use QSplitter widget.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/widgets2/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (QWidget, QHBoxLayout, QFrame,
                             QSplitter, QApplication)


# Window
WIN_TITLE="PyQt5 QSplitter"
PX=50
PY=50
WIDTH= 450
HEIGHT= 400

LINE_WIDTH =2


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# en
    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        hbox = QHBoxLayout(self)
        topleft = QFrame(self)
        topleft.setFrameShape(QFrame.Box)
        topleft.setLineWidth(LINE_WIDTH)
        topright = QFrame(self)
        topright.setFrameShape(QFrame.Box)
        topright.setLineWidth(LINE_WIDTH)
        bottom = QFrame(self)
        bottom.setFrameShape(QFrame.Box)
        bottom.setLineWidth(LINE_WIDTH)
        splitter1 = QSplitter(Qt.Horizontal)
        splitter1.addWidget(topleft)
        splitter1.addWidget(topright)
        splitter2 = QSplitter(Qt.Vertical)
        splitter2.addWidget(splitter1)
        splitter2.addWidget(bottom)
        hbox.addWidget(splitter2)
        self.setLayout(hbox)
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

