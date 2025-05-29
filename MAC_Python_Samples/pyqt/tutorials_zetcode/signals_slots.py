#  we connect a signal of a QSlider to a slot of a QLCDNumber.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/eventssignals/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (QWidget, QLCDNumber, QSlider,
                             QVBoxLayout, QApplication)


# Window
WIN_TITLE="PyQt5 Signal and Slot"
PX=50
PY=50
WIDTH= 250
HEIGHT= 150



class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        lcd = QLCDNumber(self)
        sld = QSlider(Qt.Horizontal, self)
        vbox = QVBoxLayout()
        vbox.addWidget(lcd)
        vbox.addWidget(sld)
        self.setLayout(vbox)
        sld.valueChanged.connect(lcd.display)
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
