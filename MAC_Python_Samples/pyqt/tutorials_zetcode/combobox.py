# This example shows how to use QComboBox widget.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/widgets2/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import (QWidget, QLabel,
                             QComboBox, QApplication)


# Window
WIN_TITLE="PyQt5 QComboBox"
PX=50
PY=50
WIDTH= 300
HEIGHT= 200

 # QComboBox
UBUNTU = "Ubuntu"
MANDRIVA = "Mandriva"
FEDORA = "Fedora"
ARCH = "Arch"
GENTOO = "Gentoo"


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        self.lbl = QLabel(UBUNTU, self)
        combo = QComboBox(self)
        combo.addItem(UBUNTU)
        combo.addItem(MANDRIVA)
        combo.addItem(FEDORA)
        combo.addItem(ARCH)
        combo.addItem(GENTOO)
        combo.move(50, 50)
        self.lbl.move(50, 150)
        combo.activated[str].connect(self.onActivated)
# end

    def onActivated(self, text):
        print(text)
        self.lbl.setText(text)
        self.lbl.adjustSize()
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
