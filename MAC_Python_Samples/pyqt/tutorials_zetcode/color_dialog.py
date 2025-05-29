# we select a color value　from the QColorDialog 
# and change the background color of a QFrame widget.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/dialogs/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import (QWidget, QPushButton, QFrame,
                             QColorDialog, QApplication)
from PyQt5.QtGui import QColor
import sys


# Window
WIN_TITLE="PyQt5 Color Dialog"
PX=50
PY=50
WIN_WIDTH= 300
WIN_HEIGHT= 200

# QFrame
FRM_X= 60
FRM_Y= 60
FRM_WIDTH= 100
FRM_HEIGHT= 100

FRM_FORMAT = "QWidget { background-color: %s }"

# QColor: black
R =0
G = 0
B = 0

# Button
DIALOG = "Dialog"


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIN_WIDTH, WIN_HEIGHT)
        col = QColor(R, G, B)
        self.btn = QPushButton(DIALOG, self)
        self.btn.move(20, 20)
        self.btn.clicked.connect(self.showDialog)
        self.frm = QFrame(self)
        self.frm.setStyleSheet(FRM_FORMAT % col.name())
        self.frm.setGeometry(FRM_X, FRM_Y, FRM_WIDTH,  FRM_HEIGHT)      
# end

    def showDialog(self):
        col = QColorDialog.getColor()
        print('col.name: ',  col.name() ) # QColor
        if col.isValid():
            self.frm.setStyleSheet(FRM_FORMAT % col.name())
# 3nd


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
    main()
# end

