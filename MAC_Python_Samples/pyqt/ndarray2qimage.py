# Python: load Image file using Pillow Image
# convert Pillow Image to numpy ndarray
# convert numpy ndarray to pyqt QImage
# show Image using QLabel
#  2025-04-10  K.OHWADA


from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PIL import Image
import numpy as np
import sys, os


# Window
PX=50
PY=50
WIDTH = 480
HEIGHT = 360

IMG_MODE = "RGB"

USAGE_FORMAT = "Usage: python {:s}  <image filepath>"


# https://medium.com/@bgallois/numpy-ndarray-qimage-beware-the-trap-52dcbe7388b9
def ndarray2qimage(ndarray):
    buf = ndarray.data
    height = ndarray.shape[0]
    width = ndarray.shape[1]
    stride = ndarray.strides[0]
    qimage = QImage(buf, width, height, stride, QImage.Format_RGB888)
    return qimage
# end


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


    def set_fpath(self, fpath):
        basename= os.path.basename(fpath)
        self.setWindowTitle(basename)
        pimg = Image.open(fpath)
        print('mode: ', pimg.mode)
        img_rgb = pimg.convert(IMG_MODE)
        nd_arr = np.array(img_rgb)
        print('shape: ', nd_arr.shape)
        qimg = ndarray2qimage(nd_arr)
        img_resize = resize_qimage(qimg)
        pixmap = QPixmap.fromImage(img_resize)
        self.set_pixmap(pixmap)
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

