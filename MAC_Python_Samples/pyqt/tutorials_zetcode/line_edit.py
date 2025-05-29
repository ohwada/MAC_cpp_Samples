# This example shows text 
# which is entered in QLineEdit in QLabel widget.
# Author: Jan Bodnar
# https://zetcode.com/pyqt6/widgets2/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import (QWidget, QLabel,
        QLineEdit, QApplication)


# Window
WIN_TITLE="PyQt5 QLineEdit"
PX=50
PY=50
WIDTH= 350
HEIGHT= 250


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        self.lbl = QLabel(self)
        qle = QLineEdit(self)
        qle.move(60, 100)
        self.lbl.move(60, 40)
        qle.textChanged[str].connect(self.onChanged)
# end

    def onChanged(self, text):
        print(text)
        self.lbl.setText(text)
        self.lbl.adjustSize()
# end

def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec())
# end

if __name__ == '__main__':
    main()
# end




