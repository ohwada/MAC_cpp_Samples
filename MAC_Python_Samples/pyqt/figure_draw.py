# Python: draw Figure usibg PyQt5 
# 2025-04-10  K.OHWADA

#  https://qiita.com/hoshianaaa/items/1a2552c91d42912430a2

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

WIN_TITLE = "PyQt5 Draw Demo"
PX = 10
PY = 10
WIDTH = 480
HEIGHT = 360

TEXT = "hello Python"
FONT = 'Arial'
FONT_SIZE = 20

FPATH_IMG = "python_qt_logo.png"

OUTFILE = "qt_figure_draw.png"


class Window(QWidget):
   def __init__(self):
      super(Window, self).__init__()
      self.initUI()
# end

   def initUI(self):
      self.text = TEXT
      self.setGeometry(PX, PY, WIDTH, HEIGHT)
      self.setWindowTitle(WIN_TITLE)
# end

   def paintEvent(self, event):
        self.drawPaint(self)
        img = QImage(self.size(), QImage.Format_RGB32)
        img.fill(Qt.white)
        self.drawPaint(img)
        img.save(OUTFILE)
# end

   def drawPaint(self, device):
        qp = QPainter()
        qp.begin(device)
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
        qp.drawPixmap(220,10,QPixmap(FPATH_IMG))
        qp.fillRect(20,175,130,70,QBrush(Qt.SolidPattern))
        qp.end()
# end

def main():
   app = QApplication(sys.argv)
   win = Window()
   win.show()
   sys.exit(app.exec_())

if __name__ == '__main__':
   main()
