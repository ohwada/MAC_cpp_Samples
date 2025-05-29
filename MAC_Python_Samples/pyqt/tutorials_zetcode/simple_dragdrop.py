# This is a simple drag and drop example.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/dragdrop/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import (QPushButton, QWidget,
                             QLineEdit, QApplication)


# Window
WIN_TITLE="PyQt5 Simple Drag and Drop"
PX=50
PY=50
WIDTH= 300
HEIGHT= 150

# Button
BUTTON = "Button"

# QLineEdit
EMPTY = ''

# Format
TEXT_PLAIN = "text/plain"


class Button(QPushButton):
    def __init__(self, title, parent):
        super().__init__(title, parent)
        self.setAcceptDrops(True)
# end

    def dragEnterEvent(self, e):
        if e.mimeData().hasFormat(TEXT_PLAIN):
            e.accept()
        else:
            e.ignore()
# end

    def dropEvent(self, e):
        text = e.mimeData().text()
        print('dropEvent : ', text)
        self.setText(text)
# end


class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        edit = QLineEdit(EMPTY, self)
        edit.setDragEnabled(True)
        edit.move(30, 65)
        button = Button(BUTTON, self)
        button.move(190, 65)
# end

def main():

    app = QApplication(sys.argv)
    ex = Example()
    ex.show()
    app.exec_()
# end

if __name__ == '__main__':
    main()
# end
