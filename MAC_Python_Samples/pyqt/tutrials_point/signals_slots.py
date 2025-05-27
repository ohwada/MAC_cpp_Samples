# Python: PyQt signals and slots
# 2025-04-10  K.OHWADA

#  https://www.tutorialspoint.com/pyqt5/pyqt5_signals_and_slots.htm

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

# Window
WIN_TITLE="PyQt5 Signals Slots"
PX=50
PY=50
WIDTH= 300
HEIGHT= 150

# Button
BUTTON1 =  "Button1"
BUTTON2 =  "Button2"


def window():
    win = QDialog()
    win.setGeometry(PX, PY, WIDTH,HEIGHT)
    win.setWindowTitle(WIN_TITLE)
    b1 = QPushButton(win)
    b1.setText(BUTTON1)
    b1.move(50,20)
    b1.clicked.connect(b1_clicked)
    b2 = QPushButton(win)
    b2.setText(BUTTON2)
    b2.move(50,50)
    b2.clicked.connect(b2_clicked)
    return win
# end

def b1_clicked():
   print ("Button 1 clicked")
# end

def b2_clicked():
   print ("Button 2 clicked")
# end


def main():
    app = QApplication(sys.argv)
    win = window()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
    main()  
# end
