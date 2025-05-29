# this example shows a tooltip on a window and a button.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/firstprograms/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import (QWidget, QToolTip, QPushButton, QApplication)
from PyQt5.QtGui import QFont


# Window
WIN_TITLE="PyQt5 Tooltips"
PX=50
PY=50
WIDTH= 300
HEIGHT= 200

# Tooltip
TOOLTIP_TEXT = "This is a <b>QWidget</b> widget"
BTN_TOOLTIP_TEXT = "This is a <b>QPushButton</b> widget"

# Font
# Populating font family aliases took 328 ms. Replace uses of missing font family "SansSerif" with one that exists to avoid this cost. 
# FONT_FAMILY =  "SansSerif"
FONT_FAMILY ="Arial"

FONT_SIZE = 10

# BUTTON
BUTTON = "Button"
    

class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        QToolTip.setFont(QFont(FONT_FAMILY,  FONT_SIZE))
        self.setToolTip(TOOLTIP_TEXT)
        btn = QPushButton( BUTTON, self)
        btn.setToolTip(      BTN_TOOLTIP_TEXT)
        btn.resize(btn.sizeHint())
        btn.move(50, 50)
#end 

def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
    main()
# end