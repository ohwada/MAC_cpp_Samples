# Python: display Analog Clock using QPainter
# save Anime gif using Pillow Image
# 2025-04-10  K.OHWADA

#  https://www.geeksforgeeks.org/create-analog-clock-using-pyqt5-in-python/

from PyQt5.QtWidgets import *
from PyQt5 import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PIL import Image
import io
import sys
 


WIN_TITLE = "PyQt5 Analog Clock"

PX = 10
PY = 10
WIDTH = 400
HEIGHT = 400

STYLE = "background : black;"

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
 
# Color
SEC_SCALE_COLOR = Qt.green
HOUR_COLOR =  Qt.green
MIN_COLOR =  Qt.green
SEC_COLOR = Qt.red

# Anime
UPDATE_INTERVAL = 500 # 500 msec

# Anime gif
SAVE_FORMAT = "BMP"

DURATION =  500 # msec

LOOP = 0 # endless

FRAMES = 120 # 60 sec

OUTFILE = "qt_analog_clock.gif"


# https://doloopwhile.hatenablog.com/entry/20100305/1267782841
def qimage_to_pilimage(qimage):
    buffer = QBuffer()
    buffer.open(QIODevice.WriteOnly)
    qimage.save(buffer, SAVE_FORMAT)
    fp = io. BytesIO()
    fp.write(buffer.data().data())
    buffer.close()
    fp.seek(0)
    return Image.open(fp)
# end

def create_anime_gif(images):
    images[0].save(OUTFILE,
        save_all=True,
        append_images = images[1:],
        duration= DURATION , 
        loop= LOOP
        )
    print('save ', OUTFILE)
# end


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.setStyleSheet(STYLE)
        self.initDraw()
        self.startDraw()

# end

    def initDraw(self):
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
# end

    def startDraw(self):
        self.cnt = 0
        self.is_draw_image = True
        self.list_img = []
        timer = QTimer(self)
        timer.timeout.connect(self.update)
        timer.start(UPDATE_INTERVAL)
 # end


    def drawHand(self, painter, color, rotation, pointer):
        painter.setBrush(QBrush(color))
        painter.save()
        painter.rotate(rotation)
        painter.drawConvexPolygon(pointer)
        painter.restore()
 # end


    def drawHands(self, painter):
        tik = QTime.currentTime()
        # draw each hand
        h_rotation = HOUR_DEG * (tik.hour() + tik.minute() / ONE_HOUR_MIN )
        m_rotation =  MIN_DEG * (tik.minute() + tik.second() / ONE_MIN_SEC)
        s_rotation = SEC_DEG * tik.second()
        painter.setPen(QtCore.Qt.NoPen)
        self.drawHand(painter, HOUR_COLOR,  h_rotation, self.hPointer)
        self.drawHand(painter, MIN_COLOR, m_rotation, self.mPointer)
        self.drawHand( painter, SEC_COLOR, s_rotation, self.sPointer)
# end


    def drawSecScale(self, painter):
        painter.setPen(QPen(SEC_SCALE_COLOR))
          # draw sec scale
        for i in range(0, MAX_SEC):
            if (i % SEC_SCALE_INTERVAL ) == 0:
                  painter.drawLine(LINE_X1, LINE_Y1, LINE_X2, LINE_Y2)
 # if end
            painter.rotate(SEC_DEG)
# for end


# called from a timer at 1 second intervals
    def paintEvent(self, event):
        self.drawPainter(self)
        if self.is_draw_image:
            if self.cnt < FRAMES:
                self.cnt +=1
                img = QImage(self.size(), QImage.Format_RGB32)
                img.fill(Qt.black)
                self.drawPainter(img)
                pilimage = qimage_to_pilimage(img)
                self.list_img.append(pilimage)
            elif  self.cnt == FRAMES:
                create_anime_gif(self.list_img)
                self.is_draw_image = False
# end

    def drawPainter(self, device):
    # getting minimum of width and height
        # so that clock remain square
        rec = min(self.width(), self.height())
        painter = QPainter(device)
        painter.setRenderHint(QPainter.Antialiasing)
        painter.translate(self.width() / 2, self.height() / 2)
        painter.scale(rec /  PAINTER_SCALE, rec /  PAINTER_SCALE)
        # draw background
        self.drawSecScale(painter)
        # draw hands
        self.drawHands(painter)
        painter.end()
 # class end


def main():
  app = QApplication(sys.argv)
  win = Window()
  win.show()
  exit(app.exec_())
# end


# main
if __name__ == '__main__':
    main()
# end
 



