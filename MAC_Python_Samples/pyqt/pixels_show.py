# Python: show Color Matrix Pixels using QImage
# convert Pixels to numpy array to QImage
# convert QImage to QPixmap
# show Image using QLabel
#  2025-04-10  K.OHWADA

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from pixels import Pixels
import numpy as np
import sys, os


# Window
PX=50
PY=50
WIDTH = 480
HEIGHT = 360

SIZE = 128

COLOR_MATRIX_NAME_FORMAT ="ColorMatrix_{:d}x{:d}"

USAGE_FORMAT = """
Usage: python {:s}  <num> <scale>
num:
2: 2x2 Color Matrix
3: 3x3  Color Matrix
4: 4x4  Color Matrix
8: 8x8 Checker Board Pattern
"""


# https://medium.com/@bgallois/numpy-ndarray-qimage-beware-the-trap-52dcbe7388b9
def ndarray2qimage(ndarray):
    buf = ndarray.data
    height = ndarray.shape[0]
    width = ndarray.shape[1]
    stride = ndarray.strides[0]
    qimage = QImage(buf, width, height, stride, QImage.Format_RGB888)
    return qimage
# end

def pixels2qimage(pixels):
    ndarray = np.array(pixels, np.uint8)
    qimage = ndarray2qimage(ndarray)
    return qimage
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

    def set_pixels(self, pixels, name):
        outfile = "qt_" + name + ".png"
        self.setWindowTitle(name)
        qimg = pixels2qimage(pixels)
        qimg.save(outfile)
        pixmap = QPixmap()
        pixmap.convertFromImage(qimg)
        self.set_pixmap(pixmap)
# class end


def main(pixels, name):
    app = QApplication(sys.argv)
    win = Window()
    win.set_pixels(pixels, name)
    win.show()
    sys.exit(app.exec_())
# end


def show_colorMatrix(num):
    scale = int(SIZE / num)
    size = num * scale
    name =  COLOR_MATRIX_NAME_FORMAT.format(num, num)
    print(name)
    pixels = Pixels.createColorMatrixPixels(num, scale)
    main(pixels, name)
# end


def show_checkerBoard_8x8():
    scale = int(SIZE /8)
    size = 8 * scale
    name =  "CheckerBoard_8x8"
    pixels = Pixels.createCheckerBoardPixels(8, scale)
    main(pixels, name)
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
num = int(args[1])
if (num>=2) and (num<=4) :
    show_colorMatrix(num)
elif num==8:
    show_checkerBoard_8x8()
# end


