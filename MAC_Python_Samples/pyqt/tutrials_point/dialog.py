# Python: Qt Dialog
# 2025-04-10  K.OHWADA

# https://www.tutorialspoint.com/pyqt5/pyqt5_qdialog_class.htm

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


# Window
WIN_TITLE = "PyQt Dialog demo"
PX=50
PY=50
WIDTH=200
HEIGHT=50

# Label
TEXT="Hello World!"

# Dialog
DLG_TITLE = "Dialog"


def window():
   app = QApplication(sys.argv)
   win = QWidget()
   win.setWindowTitle(WIN_TITLE)

   btn = QPushButton(win)
   btn.setText(TEXT)
   btn.move(100,50)
   btn.clicked.connect(showdialog)

   win.show()
   sys.exit(app.exec_())
# end


def showdialog():
    dlg = QDialog()
    dlg.setWindowTitle(DLG_TITLE) 
    dlg.setWindowModality(Qt.ApplicationModal)

    b1 = QPushButton("ok", dlg)
    b1.move(50,50)
    b1.clicked.connect(b1_clicked)

    dlg.exec_()
# end

def b1_clicked():
   print ("ok clicked")
# end

if __name__ == '__main__':
   window()
# end