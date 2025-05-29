#  we create a custom widget.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/customwidgets/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import (QWidget, QSlider, QApplication,
                             QHBoxLayout, QVBoxLayout)
from PyQt5.QtCore import QObject, Qt, pyqtSignal
from PyQt5.QtGui import QPainter, QFont, QColor, QPen
import sys


# Window
WIN_TITLE="PyQt5 Burning Widget"
PX=50
PY=50
WIDTH= 400
HEIGHT= 200

# QSlider
MAX_CAPACITY = 700
OVER_CAPACITY = 750

# QFont
# FONT_FAMILY = "Serif"
FONT_FAMILY = "PT Serif" # Mac

FONT_SIZE = 7

# QColor
COLOR_WHITE = QColor(255, 255, 255) # white
COLOR_GRAY = QColor(20, 20, 20) # gray
COLOR2 = QColor(255, 255, 184) # lightyellow
COLOR3 = QColor(255, 175, 175) # snow


class Communicate(QObject):
    updateBW = pyqtSignal(int)
# end


class BurningWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setMinimumSize(1, 30)
        self.value = 75
        self.num = [75, 150, 225, 300, 375, 450, 525, 600, 675]
# end

    def setValue(self, value):
        print('setValue: ', value)
        self.value = value
# end

    def paintEvent(self, e):
        qp = QPainter()
        qp.begin(self)
        self.drawWidget(qp)
        qp.end()
# end

    def drawWidget(self, qp):

        # font = QFont('Serif', 7, QFont.Light)
        font = QFont(FONT_FAMILY, FONT_SIZE)

        qp.setFont(font)
        size = self.size()
        w = size.width()
        h = size.height()
        step = int(round(w / 10))
        till = int(((w / OVER_CAPACITY) * self.value))
        full = int(((w / OVER_CAPACITY) * MAX_CAPACITY))
        if self.value >= MAX_CAPACITY:
            qp.setPen(COLOR_WHITE)
            qp.setBrush(COLOR2)
            qp.drawRect(0, 0, full, h)
            qp.setPen(COLOR3)
            qp.setBrush(COLOR3)
            qp.drawRect(full, 0, till - full, h)
        else:
            qp.setPen(COLOR_WHITE)
            qp.setBrush(COLOR2)
            qp.drawRect(0, 0, till, h)
# end

        pen = QPen( COLOR_GRAY, 1,Qt.SolidLine)
        qp.setPen(pen)
        qp.setBrush(Qt.NoBrush)
        qp.drawRect(0, 0, w - 1, h - 1)
        j = 0
        for i in range(step, 10 * step, step):
            qp.drawLine(i, 0, i, 5)
            metrics = qp.fontMetrics()
            fw = metrics.width(str(self.num[j]))
            x, y = int(i - fw/2), int(h / 2)
            qp.drawText(x, y, str(self.num[j]))
            j = j + 1
# end


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        sld = QSlider(Qt.Horizontal, self)
        sld.setFocusPolicy(Qt.NoFocus)
        sld.setRange(1, OVER_CAPACITY)
        sld.setValue(75)
        sld.setGeometry(30, 40, 150, 30)
        self.c = Communicate()
        self.wid = BurningWidget()
        self.c.updateBW[int].connect(self.wid.setValue)
        sld.valueChanged[int].connect(self.changeValue)
        hbox = QHBoxLayout()
        hbox.addWidget(self.wid)
        vbox = QVBoxLayout()
        vbox.addStretch(1)
        vbox.addLayout(hbox)
        self.setLayout(vbox)
# end

    def changeValue(self, value):
        print('changeValue: ', value)
        self.c.updateBW.emit(value)
        self.wid.repaint()
# end


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
    main()
# end
