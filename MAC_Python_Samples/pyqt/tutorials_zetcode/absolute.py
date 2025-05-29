# This example shows three labels on a window using absolute positioning.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/layout/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import QWidget, QLabel, QApplication


# Window
WIN_TITLE="PyQt5 Absolute"
PX=50
PY=50
WIDTH= 250
HEIGHT= 150

# Label
LBL1_TEXT = "ZetCode"
LBL2_TEXT =  "tutorials"
LBL3_TEXT = "for programmers"


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        lbl1 = QLabel(LBL1_TEXT, self)
        lbl1.move(15, 10)
        lbl2 = QLabel(LBL2_TEXT , self)
        lbl2.move(35, 40)
        lbl3 = QLabel(LBL3_TEXT, self)
        lbl3.move(55, 70)
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