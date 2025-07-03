# Python: animate   Bouncing  Ball using QPainter
# save Anime gif using Pillow Image
# 2025-04-10  K.OHWADA


from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from pos import Pos
from ball import *
from PIL import Image
import io
import sys


# Window
WIN_TITLE = "PyQt5  Bouncing  Ball using QPainter"
PX = 10
PY = 10
WIDTH = 400
HEIGHT = 400

# Anim
UPDATE_INTERVAL = 100 # msec

# Anime gif
SAVE_FORMAT = "BMP"

DURATION =  100 # msec

LOOP = 0 # endless

FRAMES = 600 # 60 sec

OUTFILE = "qt_anime_ball.gif"

# ball rect
rect =  getRect(WIDTH, HEIGHT, 0.2, 0.9, 0.1, 0.9)

RECT = rect

X_MIN = rect.left()

X_MAX = rect.right() - BALL_SIZE

Y_MIN = rect.top()

Y_MAX = rect.bottom()  - BALL_SIZE

X_INIT = X_MIN

Y_INIT = Y_MIN

VX_INIT =Pos.VX

VY_INIT = Pos.VY


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


class Window(QWidget):
    def __init__(self):
        super(Window, self).__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.startAnime()
# end

    def startAnime(self):
        self.pos = Pos()
        self.pos.set_range(X_MIN, X_MAX, Y_MIN, Y_MAX)
        self.pos.set_init(X_INIT, Y_INIT, VX_INIT, VY_INIT)
        self.img_ball = QPixmap(FPATH_IMG)
        self.cnt = 0
        self.is_draw_image = True
        self.list_img = []
        timer = QTimer(self)
        timer.timeout.connect(self.update)
        timer.start(UPDATE_INTERVAL) 
# end

    def paintEvent(self, e):
        x, y =  self.pos.update_pos()
        self.drawPaint(self, x, y)
        if self.is_draw_image:
            if self.cnt < FRAMES:
                self.cnt +=1
                img = QImage(self.size(), QImage.Format_RGB32)
                img.fill(Qt.white)
                self.drawPaint(img, x, y)
                pilimage = qimage_to_pilimage(img)
                self.list_img.append(pilimage)
            elif  self.cnt == FRAMES:
                create_anime_gif(self.list_img)
                self.is_draw_image = False
# end

    def drawPaint(self, device, x, y):
        qp = QPainter()
        qp.begin(device)
        qp.setPen(QColor(Qt.blue))
        qp.drawRect(RECT)
        qp.drawPixmap(int(x), int(y), self.img_ball)
        qp.end()
# end


def main():
   app = QApplication(sys.argv)
   win = Window()
   win.show()
   sys.exit(app.exec_())

if __name__ == '__main__':
   main()
