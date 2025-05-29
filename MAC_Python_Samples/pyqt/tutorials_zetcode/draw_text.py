#  we draw text in Russian Cylliric.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/painting/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import QWidget, QApplication
from PyQt5.QtGui import QPainter, QColor, QFont, QImage
from PyQt5.QtCore import Qt


# Window
WIN_TITLE = "PyQt5 Drawing Text"
PX=50
PY=50
WIDTH= 350
HEIGHT= 300

# Font
# FONT_FAMILY = "Decorative"
FONT_FAMILY = "Cinzel Decorative"

FONT_SIZE = 24

TEXT = "Лев Николаевич Толстой\nАнна Каренина"

#QColor: red
R =168
G =  34
B = 3

# QImage
OUTFILE = "qt_tutorials_zetcode_draw_text.png"


class Windows(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        self.text = TEXT
# end

    def paintEvent(self, event):
        img = QImage(self.size(), QImage.Format_RGB32)
        img.fill(Qt.white)
        self.drawPaint( event, img)
        img.save(OUTFILE)
        self. drawPaint( event, self)
# end

    def drawPaint(self,  event, device):
        qp = QPainter()
        qp.begin(device)
        self.drawText(event, qp)
        qp.end()
# end

    def drawText(self, event, qp):
        qp.setPen(QColor(R, G, B) )
        qp.setFont(QFont(FONT_FAMILY, FONT_SIZE))
        qp.drawText(event.rect(), Qt.AlignCenter, self.text)
# end


def main():
    app = QApplication(sys.argv)
    win = Windows()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
    main()
# end

