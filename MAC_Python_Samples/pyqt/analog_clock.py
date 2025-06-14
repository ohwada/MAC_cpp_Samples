# Python: Analog Clock with Qt5
# 2025-04-10  K.OHWADA

#  https://www.geeksforgeeks.org/create-analog-clock-using-pyqt5-in-python/

from PyQt5.QtWidgets import *
from PyQt5 import QtCore, QtGui
from PyQt5.QtGui import *
from PyQt5.QtCore import *
import sys
 


WIN_TITLE = 'Analog Clock'

PX = 10
PY = 10
WIDTH = 500
HEIGHT = 500

STYLE = "background : black;"

UPDATE_INTERVAL = 1000 # 1 sec

# time for the hand to rotate one lap
# ONE_LAP_HOUR = 12 # 12 houurs
# ONE_LAP_MIN = 60 # 60 minutess = one hour
# ONE_LAP_SEC = 60 # 60 secinds = one minute

# angle per unit time
SEC_DEG = 6 # 360/NE_LAP_SEC
MIN_DEG = 6 # 360/ONE_LAP_MIN
HOUR_DEG = 30 # 360/# ONE_LAP_HOUR

# unit conversion
ONE_HOUR_MIN = 60 # one hour = 60minutes
ONE_MIN_SEC = 60 # one minute = 60 srconds

# second hand scale placed every 5 seconds on the outer circle
MAX_SEC = 60 # same ONE_LAP_SEC

SEC_SCALE_INTERVAL = 5

PAINTER_SCALE = 200

# sec scale
LINE_X1 = 87
LINE_Y1  = 0 
LINE_X2 = 97
LINE_Y2 =0

  # hour hand
HOUR_X1 = 6
HOUR_Y1 = 7
HOUR_X2 = -6
HOUR_Y2 = 7
HOUR_X3 = 0
HOUR_Y3 = -50

# minute hand    
MIN_X1 = 6
MIN_Y1 = 7  
MIN_X2 = -6
MIN_Y2 = 7   
MIN_X3 = 0
MIN_Y3 = -70                        

# second hand
SEC_X1 = 1
SEC_Y1 = 1 
SEC_X2 = -1
SEC_Y2 = 1 
SEC_X3 = 0
SEC_Y3 = -90
 

class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        timer = QTimer(self)
        timer.timeout.connect(self.update) # call paintEvent
        timer.start(UPDATE_INTERVAL)
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.setStyleSheet(STYLE)
        # hour hand
        self.hPointer = QtGui.QPolygon([QPoint(HOUR_X1, HOUR_Y1),
                                        QPoint(HOUR_X2, HOUR_Y2),
                                        QPoint(HOUR_X3, HOUR_Y3)])
        # minute hand
        self.mPointer = QPolygon([QPoint(MIN_X1, MIN_Y1),
                                  QPoint(MIN_X2, MIN_Y2),
                                  QPoint(MIN_X3, MIN_Y3)])
        # second hand
        self.sPointer = QPolygon([QPoint(SEC_X1, SEC_Y1),
                                  QPoint(SEC_X2, SEC_Y2),
                                  QPoint(SEC_X2, SEC_Y3)])
        # color for minute and hour hand: green
        self.bColor = Qt.green
        # color for second hand: red
        self.sColor = Qt.red
 # end

    # method for paint event
# called from a timer at 1 second intervals
    def paintEvent(self, event):
        # getting minimum of width and height
        # so that clock remain square
        rec = min(self.width(), self.height())
        # current time
        tik = QTime.currentTime()
        painter = QPainter(self)

# inner function
 # method to draw the hands
# argument : color rotation and which hand should be pointed
        def drawPointer(color, rotation, pointer):
            painter.setBrush(QBrush(color))
            painter.save()
            painter.rotate(rotation)
            painter.drawConvexPolygon(pointer)
            painter.restore()
 # end

        painter.setRenderHint(QPainter.Antialiasing)
        painter.translate(self.width() / 2, self.height() / 2)
        painter.scale(rec /  PAINTER_SCALE, rec /  PAINTER_SCALE)
        painter.setPen(QtCore.Qt.NoPen)
        # draw each hand
        drawPointer(self.bColor, (HOUR_DEG * (tik.hour() + tik.minute() / ONE_HOUR_MIN )), self.hPointer)
        drawPointer(self.bColor, (MIN_DEG * (tik.minute() + tik.second() / ONE_MIN_SEC)), self.mPointer)
        drawPointer(self.sColor, (SEC_DEG * tik.second()), self.sPointer)
        # drawing background
        painter.setPen(QPen(self.bColor))
          # draw sec scale
        for i in range(0, MAX_SEC):
            if (i % SEC_SCALE_INTERVAL ) == 0:
                painter.drawLine(LINE_X1, LINE_Y1, LINE_X2, LINE_Y2)
 # if end
            painter.rotate(SEC_DEG)
# for end
        painter.end()
 # class end


# main
if __name__ == '__main__':
  app = QApplication(sys.argv)
  win = Window()
  win.show()
  exit(app.exec_())
# end
 



