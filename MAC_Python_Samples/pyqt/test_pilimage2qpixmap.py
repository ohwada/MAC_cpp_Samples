# Python: load Image file using Pillow Image
# convert Pillow Image to pyqt QPixmap
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

# Transparent png should be "PNG"
SAVE_FORMAT = "BMP"


# https://doloopwhile.hatenablog.com/entry/20100305/1267782841
def pilimage2qpixmap(pilimage):
    buffer = QBuffer()
    buffer.open(QIODevice.WriteOnly)
    pilimage.save(buffer, SAVE_FORMAT )
    pixmap = QPixmap()
    pixmap.loadFromData(buffer.data().data(), SAVE_FORMAT )
    return pixmap

def resize_pixmap(pixmap):
    img = pixmap.copy()
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
        pimg = Image.open(fpath)
        pixmap = pilimage2qpixmap(pimg)
        pixmap_resize = resize_pixmap(pixmap)
        self.set_pixmap(pixmap_resize)
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

