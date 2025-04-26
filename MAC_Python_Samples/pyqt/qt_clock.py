# Python: Dejital Clock with PyQt
# 2025-04-10  K.OHWADA

#  https://qiita.com/kenasman/items/73d01df973a25ae704e4

import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

# window 
TITLE = 'Digital Clock'
WIDTH = 500
HEIGHT = 150

# clock
FORMAT = 'hh:mm:ss'
DIGITS = 8
INTERVAL = 1000 # 1 sec


class TestTimer(QWidget):
    def __init__(self, parent=None):
        super(TestTimer, self).__init__(parent)
        self.setWindowTitle(TITLE )
        timer = QTimer(self)
        timer.timeout.connect(self.updtTime)
        self.testTimeDisplay = QLCDNumber(self)
        self.testTimeDisplay.setSegmentStyle(QLCDNumber.Filled)
        self.testTimeDisplay.setDigitCount(DIGITS)
        self.testTimeDisplay.resize(WIDTH,  HEIGHT)
        self.updtTime()
        timer.start( INTERVAL )
# end

    def updtTime(self):
        currentTime = QDateTime.currentDateTime().toString(FORMAT)
        self.testTimeDisplay.display(currentTime)
# end

if __name__ == '__main__':
    myApp = QApplication(sys.argv)
    myWindow = TestTimer()
    myWindow.show()
    myApp.exec_()
    sys.exit()
# end


