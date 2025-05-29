#   we reimplement an event handler.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/eventssignals/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QWidget, QApplication


# Window
WIN_TITLE="PyQt5  Key Press Event"
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
# end

    def keyPressEvent(self, e):
        print('keyPressEvent')
        key = e.key()
        if key == Qt.Key_Escape:
            print('Escape')
            self.close()
        elif key == Qt.Key_Tab:
            print('Tab')
        else:
            print(key)
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