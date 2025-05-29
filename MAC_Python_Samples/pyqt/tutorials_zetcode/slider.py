#  This example shows a QSlider widget.
# Author: Jan Bodnar
#  https://zetcode.com/pyqt6/widgets/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import (QWidget, QSlider,
        QLabel, QApplication)
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPixmap
import sys


# Window
WIN_TITLE="PyQt5 QSlider"
PX=50
PY=50
WIDTH= 350
HEIGHT= 250


# Icon
FPATH_MUTE_ICON = "mute.png"
FPATH_MIN_ICON = "min.png"
FPATH_MED_ICON = "med.png"
FPATH_MAX_ICON = "max.png"


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        sld = QSlider(Qt.Orientation.Horizontal, self)
        sld.setFocusPolicy(Qt.FocusPolicy.NoFocus)
        sld.setGeometry(30, 40, 200, 30)
        sld.valueChanged[int].connect(self.changeValue)
        self.label = QLabel(self)
        self.label.setPixmap(QPixmap(FPATH_MUTE_ICON))
        self.label.setGeometry(250, 40, 80, 30)
# end

    def changeValue(self, value):
# minimum defaults to 0, the maximum to 99

        if value == 0:
            self.label.setPixmap(QPixmap(FPATH_MUTE_ICON))
        elif 0 < value <= 30:
            self.label.setPixmap(QPixmap(FPATH_MIN_ICON))
        elif 30 < value < 80:
            self.label.setPixmap(QPixmap(FPATH_MED_ICON))
        elif 80 <= value:
            self.label.setPixmap(QPixmap(FPATH_MAX_ICON))
# end

def main():
    app = QApplication(sys.argv)
    win =  Window()
    win.show()
    sys.exit(app.exec())
# end

if __name__ == '__main__':
    main()
# end
