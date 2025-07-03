# Python: draw Shapes using QPainter
# save file using QImage
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

TEXT = "Hello Python"
FONT = 'Arial'
FONT_SIZE = 20

FPATH_IMG = "python_qt_logo.png"

OUTFILE = "qt_draw_shapes_painter.png"


class Window(QWidget):
   def __init__(self):
        super(Window, self).__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
# end

   def paintEvent(self, event):
        self.drawPaint(self)
        img = QImage(self.size(), QImage.Format_RGB32)
        img.fill(Qt.white)
        self.drawPaint(img)
        img.save(OUTFILE)
        print('save ',OUTFILE)
# end

   def drawPaint(self, device):
        pen_black = QPen(QColor(Qt.black), 2)
        pen_red = QPen(QColor(Qt.red))
        pen_green = QPen(QColor(Qt.green), 2)
        pen_blue = QPen(QColor(Qt.blue), 2)
        brush_cyan = QBrush(QColor(Qt.cyan))        
        qp = QPainter()
        qp.begin(device)
        qp.setPen(pen_red)
        qp.setFont(QFont(FONT, FONT_SIZE))
        qp.drawText(10,50, TEXT)
        qp.setPen(pen_blue)
        qp.drawLine(20,100,150,100)
        qp.setPen(pen_green)
        qp.drawRect(20,150,150,100)
        qp.fillRect(30,175,130,70,QBrush(Qt.SolidPattern))
        qp.setPen(pen_black)
        qp.setBrush(brush_cyan)
        qp.drawEllipse(200,50,70,100)
        qp.drawPixmap(300, 50, QPixmap(FPATH_IMG))
        qp.end()
# end

def main():
   app = QApplication(sys.argv)
   win = Window()
   win.show()
   sys.exit(app.exec_())

if __name__ == '__main__':
   main()
