# Python: Clipboard
# 2025-04-10  K.OHWADA

#  https://www.tutorialspoint.com/pyqt5/pyqt5_qclipboard.htm

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


# Window
WIN_TITLE ="PyQt5 Clipboard"
PX=50
PY=50
WIDTH=300
HEIGHT=200



COPY = "Copy"
PASTE = "Paste"


# Label
TEXT="Hello World!"


class Window(QWidget):
    def __init__(self):
        super( Window, self).__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        self.initUI()
# end

    def initUI(self):
      hbox = QVBoxLayout()
      self.edit1=QTextEdit()
      hbox.addWidget(self.edit1)
      self.btn1=QPushButton(COPY)
      hbox.addWidget(self.btn1)
      self.edit2=QTextEdit()
      self.btn2=QPushButton(PASTE)
      hbox.addWidget(self.edit2)
      hbox.addWidget(self.btn2)
      self.btn1.clicked.connect(self.copytext)
      self.btn2.clicked.connect(self.pastetext)
      self.setLayout(hbox)
  # end

    def copytext(self):
      #clipboard.setText(self.edit1.copy())
      self.edit1.copy()
      print (clipboard.text())
      msg=QMessageBox()
      msg.setText(clipboard.text()+" copied on clipboard")
      msg.exec_()
# end

    def pastetext(self):
      self.edit2.setText(clipboard.text())
# end

# main
app = QApplication(sys.argv)
clipboard=app.clipboard()
win =  Window()
win.show() 
sys.exit(app.exec_())


