# Python: Qt  Message Box
# 2025-04-10  K.OHWADA

#  https://www.tutorialspoint.com/pyqt5/pyqt5_qmessagebox.htm

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


# Window
WIN_TITLE= "PyQt MessageBox demo"
PX=50
PY=50
WIDTH=200
HEIGHT=50

# Button
BTN_TEXT = "Show message!"

# Message Box
MSG_WIN_TITLE = "MessageBox demo"

MSG_TEXT ="This is a message box"

DETAILED_TEXT = "The details are as follows:"

INFORMATIVE_TEXT = "This is additional information"


def window():
    app = QApplication(sys.argv)
    win = QWidget()
    win.setWindowTitle(WIN_TITLE)

    b = QPushButton(win)
    b.setText(BTN_TEXT)
    b.move(100,50)
    b.clicked.connect(showdialog)

    win.show()
    sys.exit(app.exec_())
# end

def showdialog():
    msg = QMessageBox()
    msg.setIcon(QMessageBox.Information)
    msg.setWindowTitle( MSG_WIN_TITLE)
    msg.setDetailedText(   DETAILED_TEXT)
    msg.setText( MSG_TEXT)
    msg.setInformativeText(INFORMATIVE_TEXT)
    msg.setStandardButtons(QMessageBox.Ok | QMessageBox.Cancel)
    msg.buttonClicked.connect(msgbtn)
    retval = msg.exec_()
# end

def msgbtn(i):
   print ("Button pressed is:", i.text())
# end

if __name__ == '__main__':
   window()
# end

