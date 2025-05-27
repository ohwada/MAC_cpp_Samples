# Python: PyQt Drag Drop
# 2025-04-10  K.OHWADA

#  https://www.tutorialspoint.com/pyqt5/pyqt5_drag_and_drop.htm
# https://qiita.com/hoshianaaa/items/4eab0a936a9232e8a5f3

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import sys

# Window
WIN_TITLE= "PyQt5 Simple Drag and Drop"
PX=50
PY=50
WIDTH=200
HEIGHT=100

# Label
TEXT= "Type some text in textbox and drag it into combo box"


class combo(QComboBox):
    def __init__(self, title, parent):
        super(combo, self).__init__( parent)
        self.setAcceptDrops(True)
# end

    def dragEnterEvent(self, e):
        print ('dragEnterEvent')
        if e.mimeData().hasText():
            e.accept()
        else:
            e.ignore()
# end

    def dropEvent(self, e):
        text = e.mimeData().text()
        print('dropEvent: ', text)
        self.addItem(text)
# end

class Window(QWidget):
    def __init__(self):
        super(Window, self).__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        self.initUI()
# end

    def initUI(self):
        lo = QFormLayout()
        lo.addRow( QLabel(TEXT) )
        edit = QLineEdit()
        edit.setDragEnabled(True)
        com = combo("Button", self)
        lo.addRow(edit,com)
        self.setLayout(lo)
# end


def main():
   app = QApplication(sys.argv)
   win = Window()
   win.show()
   app.exec_()
# end

if __name__ == '__main__':
   main()
# END
