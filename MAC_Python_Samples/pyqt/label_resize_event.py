# Python: automatically change Font Size when Window( CustomLabel) is resized
# 2025-04-10  K.OHWADA

# https://qiita.com/marksard/items/7afeb3ab3ffa61ae8d27


from PyQt5 import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import sys

# window
WIN_TITLE =  "Resize Event"
PX=50
PY=50
WIDTH = 100
HEIGHT = 200


# Font
# FONT_FAMILY = '源ノ角ゴシック Code JP M'
FONT_FAMILY ="Arial"

FONT_SCALE = 1.0
FONT_SCALE_B = 2.0

TEXT = 'Q'

# style
STYLE = 'QWidget{background-color:#1976D2;} QLabel{color:#FFFFFF; background-color:#2196F3; border-color:#FF9800;}'

MARGIN_LEFT = 5 
MARGIN_TOP = 5 
MARGIN_RIGHT = 5
MARGIN_BOTTOM = 5


class CustomLabel(QLabel):
    def __init__(self, text):
        super(CustomLabel, self).__init__(text)
        self._font = QFont()
        self.setFont(self._font)
        self.setAlignment(QtCore.Qt.AlignVCenter | QtCore.Qt.AlignHCenter)
        self.setSizePolicy(QSizePolicy.Ignored, QSizePolicy.Ignored)
        self._fontScale =  FONT_SCALE
# end

    def setFontFamily(self, face):
        self._font.setFamily(face)
# end

    def setFontScale(self, scale):
        self._fontScale = scale
# end

    def resizeEvent(self, evt):
        width = self.size().width() / len(self.text())
        height = self.size().height()
        baseSize =  0
        if width > height:
            baseSize = height
        else:
            baseSize = width
# if end
        self._font.setPixelSize( int(baseSize * self._fontScale) )
        self.setFont(self._font)
# end


def window():
    app = QApplication(sys.argv)
    app.setStyleSheet( STYLE)
    win = QWidget()
    win.setWindowTitle(WIN_TITLE)
    win.setGeometry(PX, PY, WIDTH, HEIGHT)
    layout = QGridLayout()
    layout.setContentsMargins(MARGIN_LEFT, MARGIN_TOP, MARGIN_RIGHT, MARGIN_BOTTOM)
    win.setLayout(layout)

    labelA = CustomLabel(TEXT)
    labelA.setFontFamily(FONT_FAMILY)
    layout.addWidget(labelA, 0, 0)

    labelB = CustomLabel(TEXT) 
    labelB.setFontFamily(FONT_FAMILY)
    labelB.setFontScale(FONT_SCALE_B)
    layout.addWidget(labelB, 0, 1)

    win.show()
    sys.exit(app.exec_())
# end


# main
window()


