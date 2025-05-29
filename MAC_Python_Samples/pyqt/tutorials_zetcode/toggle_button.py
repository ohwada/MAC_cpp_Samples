#  we create three toggle buttons.
# They control the background color of a QFrame.
# Author: Jan Bodnar
#  https://zetcode.com/pyqt6/widgets/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import (QWidget, QPushButton,
        QFrame, QApplication)
from PyQt5.QtGui import QColor
import sys


# Window
WIN_TITLE="PyQt5 Toggle Button"
PX=50
PY=50
WIDTH= 300
HEIGHT= 250

# Button
RED = "Red"
GREEN = "Green"
BLUE = "Blue"

# QColor
R = 0
G = 0
B = 0

# QFrame StyleSheet
FORMAT = "QWidget { background-color: %s }"


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end
    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        self.col = QColor(R, G,  B)
        redb = QPushButton(RED, self)
        redb.setCheckable(True)
        redb.move(10, 10)
        redb.clicked[bool].connect(self.setColor)
        greenb = QPushButton(GREEN, self)
        greenb.setCheckable(True)
        greenb.move(10, 60)
        greenb.clicked[bool].connect(self.setColor)
        blueb = QPushButton(BLUE, self)
        blueb.setCheckable(True)
        blueb.move(10, 110)
        blueb.clicked[bool].connect(self.setColor)
        self.square = QFrame(self)
        self.square.setGeometry(150, 20, 100, 100)
        self.square.setStyleSheet(FORMAT % self.col.name())
# end

    def setColor(self, pressed):
        source = self.sender()
        text = source.text()
        print('source.text: ', text)
        if pressed:
            val = 255
        else:
            val = 0
# end
        if text == RED:
            self.col.setRed(val)
        elif text == GREEN:
            self.col.setGreen(val)
        elif text == BLUE:
            self.col.setBlue(val)
# end
        self.square.setStyleSheet(FORMAT % self.col.name())
# end

def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec())
# end

if __name__ == '__main__':
    main()# end