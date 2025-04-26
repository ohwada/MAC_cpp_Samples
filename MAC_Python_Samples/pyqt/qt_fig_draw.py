# Python: draw figure usibg PyQt5 
# 2025-04-10  K.OHWADA

#  https:https://qiita.com/hoshianaaa/items/1a2552c91d42912430a2

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

WIN_TITLE = "PyQt5 Draw Demo"
PX = 10
PY = 10
WIDTH  = 400
HEIGHT = 300

TEXT = "hello Python"
FONT = 'Arial'
FONT_SIZE = 20


class Example(QWidget):
   def __init__(self):
      super(Example, self).__init__()
      self.initUI()
# end

   def initUI(self):
      self.text = TEXT
      self.setGeometry(PX, PY, WIDTH, HEIGHT)
      self.setWindowTitle(WIN_TITLE)
      self.show()
# end

   def paintEvent(self, event):
      qp = QPainter()
      qp.begin(self)

# draw line
      qp.setPen(QColor(Qt.red))
      qp.setFont(QFont(FONT, FONT_SIZE))
      qp.drawText(10,50, TEXT)
      qp.setPen(QColor(Qt.blue))

 # draw line
      qp.drawLine(10,100,100,100)
      qp.drawRect(10,150,150,100)
      qp.setPen(QColor(Qt.yellow))
      qp.drawEllipse(100,50,100,50)
      qp.fillRect(20,175,130,70,QBrush(Qt.SolidPattern))
      qp.end()
# end

def main():
   app = QApplication(sys.argv)
   ex = Example()
   sys.exit(app.exec_())

if __name__ == '__main__':
   main()
