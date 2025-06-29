# Python: load Image file using Pillow Image
# convert Pillow Image to pyqt QImage
# show Image using QLabel
#  2025-04-10  K.OHWADA


from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PIL import Image
import io
import sys, os


# Window
PX=50
PY=50
WIDTH = 480
HEIGHT = 360

USAGE_FORMAT = "Usage: python {:s}  <image filepath>"

SAVE_FORMAT = "BMP"


# https://doloopwhile.hatenablog.com/entry/20100305/1267782841
def pilimage2qimage(pilimage):
    buffer = QBuffer()
    buffer.open(QIODevice.WriteOnly)
    pilimage.save(buffer, SAVE_FORMAT )
    qimage = QImage()
    qimage.loadFromData(buffer.data().data(), SAVE_FORMAT )
    return qimage

def resize_qimage(qimg):
    img = qimg.copy()
    iw = img.width()
    ih = img.height()
    print('original: ', iw, ih)
    if (iw> WIDTH) or (ih > HEIGHT):
        width = int(0.9*WIDTH)
        height = int(0.9*HEIGHT)
        img = img.scaled(width, height, Qt.KeepAspectRatio,Qt.FastTransformation)
        w = img.width()
        h = img.height()
        print('resize:', w, h)
# end
    return img
# end


def load_img(fpath):
    pimg = Image.open(fpath)
    qimg = pilimage2qimage(pimg)
    img = resize_qimage(qimg)
    pixmap = QPixmap.fromImage(img)
    return  pixmap
# end


class Window(QMainWindow):
    def __init__(self):
        super(Window, self).__init__()
        self.setGeometry( PX, PY, WIDTH, HEIGHT)
# end

    def set_pixmap(self, pixmap):
    label = QLabel(self)
    iw = pixmap.width()
    ih = pixmap.height()
    x = (WIDTH - iw)//2
    y = (HEIGHT - ih)//2
    label.setGeometry(x, y, iw, ih)
    label.setPixmap(pixmap)
# end

    def set_fpath(self,fpath):
        basename= os.path.basename(fpath)
        self.setWindowTitle(basename)
        pixmap =load_img(fpath)
        self.set_pixmap(pixmap)
# def end
# class end



def main(fpath):
    app = QApplication(sys.argv)
    win = Window()
    win.set_fpath(fpath)
    win.show()
    sys.exit(app.exec_())
# end


def usage(script):
    usage = USAGE_FORMAT.format(script)
    print(usage)
# end


# main
args = sys.argv
argc = len(args)
if argc < 2:
    usage(args[0])
    exit()
# end
main(args[1])

