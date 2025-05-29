# we create a skeleton of a calculator using QGridLayout.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/layout/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import (QWidget, QGridLayout,
                             QPushButton, QApplication)


# Window
WIN_TITLE="PyQt5 Calculator"
PX=50
PY=50
WIDTH= 300
HEIGHT= 300

# Button
NAMES = ['Cls', 'Bck', '', 'Close',
                 '7', '8', '9', '/',
                 '4', '5', '6', '*',
                 '1', '2', '3', '-',
                 '0', '.', '=', '+']


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        grid = QGridLayout()
        self.setLayout(grid)
        positions = [(i, j) for i in range(5) for j in range(4)]
        for position, name in zip(positions, NAMES):
            if name == '':
                continue
            button = QPushButton(name)
            grid.addWidget(button, *position)
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
