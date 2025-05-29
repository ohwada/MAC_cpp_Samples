#  we display the x and y coordinates of a mouse pointer in a label widget.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/eventssignals/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QWidget, QApplication, QGridLayout, QLabel


# Window
WIN_TITLE="PyQt5  Mouse Move Event "
PX=50
PY=50
WIDTH= 450
HEIGHT= 300


class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        grid = QGridLayout()
        x = 0
        y = 0
        self.text = f'x: {x},  y: {y}'
        self.label = QLabel(self.text, self)
        grid.addWidget(self.label, 0, 0, Qt.AlignTop)
        self.setMouseTracking(True)
        self.setLayout(grid)
        self.setGeometry(300, 300, 450, 300)
        self.setWindowTitle('Event object')
        self.show()
# end

    def mouseMoveEvent(self, e):
        x = e.x()
        y = e.y()
        text = f'x: {x},  y: {y}'
        self.label.setText(text)
# end


def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()

