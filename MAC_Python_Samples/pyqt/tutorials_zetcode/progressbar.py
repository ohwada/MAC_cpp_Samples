#  This example shows a QProgressBar widget.
# Author: Jan Bodnar
#  https://zetcode.com/pyqt6/widgets/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import (QWidget, QProgressBar,
        QPushButton, QApplication)
from PyQt5.QtCore import QBasicTimer
import sys


# Window
WIN_TITLE="PyQt5 QProgressBar"
PX=50
PY=50
WIDTH= 280
HEIGHT= 170

# Button
START = "Start"
STOP = "Stop"
FINISHED= "Finished"


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        self.pbar = QProgressBar(self)
        self.pbar.setGeometry(30, 40, 200, 25)
        self.btn = QPushButton(START, self)
        self.btn.move(40, 80)
        self.btn.clicked.connect(self.doAction)
        self.timer = QBasicTimer()
        self.step = 0
# end

    def timerEvent(self, e):
        if self.step >= 100:
            self.timer.stop()
            self.btn.setText(FINISHED)
            return
# end
        self.step = self.step + 1
        self.pbar.setValue(self.step)
# end

    def doAction(self):
        if self.timer.isActive():
            self.timer.stop()
            self.btn.setText(START)
        else:
            self.timer.start(100, self)
            self.btn.setText(STOP)
# end

def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec())
# end

if __name__ == '__main__':
    main()
# end
