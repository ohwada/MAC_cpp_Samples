# Python: animate Color using QPropertyAnimation
# 2025-04-10  K.OHWADA

# https://zetcode.com/pyqt/qpropertyanimation/


from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
import sys

# Window
WIN_TITLE =  "PyQt5 anime Color"
PX=50
PY=50
WIDTH = 480
HEIGHT = 360

SPACING = 40

# Label
TEXT = "Summer"

FONT_SIZE = 35

# Button
START = "Start"

# Anime
# black
START_R = 0
START_G = 0
START_B = 0

# red
END_R = 255
END_G = 100
END_B = 100

DURATION = 2500 # 2.5 sec
LOOP_COUNT = 2

class CustomLabel(QLabel):
    def __init__(self, text):
        super().__init__(text)
# end

    def _set_color(self, col):
        palette = self.palette()
        palette.setColor(self.foregroundRole(), col)
        self.setPalette(palette)
# def end
    color = pyqtProperty(QColor, fset=_set_color)
# class end

class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.initUI()
# end

    def initUI(self):
# label
        self.label = CustomLabel(TEXT)
        font = self.label.font()
        font.setPointSize( FONT_SIZE)
        self.label.setFont(font)
# button
        button = QPushButton(START, self)
        button.setSizePolicy(QSizePolicy.Policy.Fixed,
                                  QSizePolicy.Policy.Fixed)
        button.clicked.connect(self.doAnim)
# hbox
        hbox = QHBoxLayout(self)
        hbox.addWidget(button)
        hbox.addSpacing(SPACING)
        hbox.addWidget(self.label)
# end

    def doAnim(self):
        self.anim = QPropertyAnimation(self.label, b"color")
        self.anim.setStartValue(QColor(START_R, START_G, START_B))
        self.anim.setEndValue(QColor(END_R, END_G, END_B))
        self.anim.setDuration(DURATION)
        self.anim.setLoopCount(LOOP_COUNT)
        self.anim.start()
# end


def main():
    app = QApplication([])
    win = Window()
    win.show()
    sys.exit(app.exec())
# end

if __name__ == "__main__":
    main()
# end
