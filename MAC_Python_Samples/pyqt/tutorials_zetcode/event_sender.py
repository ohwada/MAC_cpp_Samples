#  we determine the event sender object.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/eventssignals/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import QMainWindow, QPushButton, QApplication


# Window
WIN_TITLE="PyQt5 Event Sender"
PX=50
PY=50
WIDTH= 350
HEIGHT= 250

#utton 
BTN1_TEXT = "Button 1"
BTN2_TEXT = "Button 2"


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        btn1 = QPushButton(  BTN1_TEXT, self)
        btn1.move(30, 50)
        btn2 = QPushButton( BTN2_TEXT, self)
        btn2.move(150, 50)
        btn1.clicked.connect(self.buttonClicked)
        btn2.clicked.connect(self.buttonClicked)
        self.statusBar()
# end

    def buttonClicked(self):
        sender = self.sender()
        print('buttonClicked: ', sender.text())
        self.statusBar().showMessage(sender.text() + ' was pressed')
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
