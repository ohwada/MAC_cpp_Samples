# This program creates a quit button. 
# When we press the button, the application terminates.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/firstprograms/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import QWidget, QPushButton, QApplication
import sys


# Window
WIN_TITLE="PyQt5  'Quit Button"
PX=50
PY=50
WIDTH= 200
HEIGHT= 100

# Button
QUIT = 'Quit'


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        qbtn = QPushButton(QUIT, self)
        qbtn.clicked.connect(QApplication.instance().quit)
        qbtn.resize(qbtn.sizeHint())
        qbtn.move(50, 50)
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