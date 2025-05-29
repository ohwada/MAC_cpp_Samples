# we select a font name
# and change the font of label.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/dialogs/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import (QWidget, QVBoxLayout, QPushButton,
                             QSizePolicy, QLabel, QFontDialog, QApplication)
import sys


# Window
WIN_TITLE="PyQt5 Font Dialog"
PX=50
PY=50
WIDTH= 300
HEIGHT= 200

# button
DIALOG = "Dialog"

# Label
LABEL_TEXT = "Knowledge only matters"


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        vbox = QVBoxLayout()
        btn = QPushButton(DIALOG, self)
        btn.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        btn.move(20, 20)
        vbox.addWidget(btn)
        btn.clicked.connect(self.showDialog)
        self.lbl = QLabel(LABEL_TEXT, self)
        self.lbl.move(130, 20)
        vbox.addWidget(self.lbl)
        self.setLayout(vbox)
# end


# It's not legal to call -layoutSubtreeIfNeeded on a view which is already being laid out.  
# If you are implementing the view's -layout method, you can call -[super layout] instead. Break on void _NSDetectedLayoutRecursion(void) to debug.  
# This will be logged only once.  This may break in the future.
    def showDialog(self):
        font, ok = QFontDialog.getFont()
        print('font.family: ', font.family()) # QFont
        if ok:
            self.lbl.setFont(font)
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
