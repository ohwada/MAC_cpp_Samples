#   we can press on a button with left mouse click 
# or drag and drop the button with  the right mouse click.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/dragdrop/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtCore import Qt, QMimeData
from PyQt5.QtGui import QDrag
from PyQt5.QtWidgets import QPushButton, QWidget, QApplication


# Window
WIN_TITLE="PyQt5 Mouse Click or Move"
PX=50
PY=50
WIDTH= 400
HEIGHT= 300

# Button
BUTTON = "Button"

# QLineEdit
EMPTY = ''

# Format
TEXT_PLAIN = "text/plain"


class Button(QPushButton):
    def __init__(self, title, parent):
        super().__init__(title, parent)
# end

    def mouseMoveEvent(self, e):  
        if e.buttons() != Qt.RightButton: # PyQt5.QtCore.Qt.MouseButtons
            return
# end
        print('mouseMoveEvent: ', e.pos() )
        mimeData = QMimeData()
        drag = QDrag(self)
        drag.setMimeData(mimeData)
        drag.setHotSpot(e.pos() - self.rect().topLeft())
        dropAction = drag.exec_(Qt.MoveAction)
# end

    def mousePressEvent(self, e):
        super().mousePressEvent(e)
        button = e.button()
        if button== Qt.LeftButton:
            print('mousePressEvent: LeftButton')
        elif  button == Qt.RightButton:
            print('mousePressEvent: rightButton')
# end


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        self.setAcceptDrops(True)
        self.button = Button(BUTTON , self)
        self.button.move(100, 65)
# end

    def dragEnterEvent(self, e):
        print( 'dragEnterEvent')
        e.accept()
# end

    def dropEvent(self, e):
        position = e.pos() # PyQt5.QtCore.QPoint
        print( 'dropEvent: ', position)
        self.button.move(position)
        e.setDropAction(Qt.MoveAction)
        e.accept()
# end


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    app.exec_()
# end

if __name__ == '__main__':
    main()
# end

