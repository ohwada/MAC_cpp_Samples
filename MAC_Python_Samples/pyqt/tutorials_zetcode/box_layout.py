# we position two push buttons in the bottom-right corner of the window.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/layout/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import (QWidget, QPushButton,
                             QHBoxLayout, QVBoxLayout, QApplication)


# Window
WIN_TITLE="PyQt5 Buttons"
PX=50
PY=50
WIDTH= 300
HEIGHT= 150

OK = "OK"
CANCEL = "Cancel"




class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        okButton = QPushButton(OK )
        cancelButton = QPushButton(CANCEL)
        okButton.clicked.connect(self.do_okButton)
        cancelButton.clicked.connect(self.do_cancelButton)
        hbox = QHBoxLayout()
        hbox.addStretch(1)
        hbox.addWidget(okButton)
        hbox.addWidget(cancelButton)
        vbox = QVBoxLayout()
        vbox.addStretch(1)
        vbox.addLayout(hbox)
        self.setLayout(vbox)
# end

    def do_okButton(self):
        print('okButton')
# end

    def do_cancelButton(self):
        print('cancelButton')
# end


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
    main()# end
