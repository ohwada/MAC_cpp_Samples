# Python: load Image file using QPixmap
# show Image using QLabel
# If Image is large than Window, show Image in resized size
 # suport jpeg
#  2025-04-10  K.OHWADA

import pyqtgraph as pg

import numpy as np
import sys, os


# Window
PX=50
PY=50
WIDTH = 480
HEIGHT = 360


USAGE_FORMAT = "Usage: python {:s}  <image filepath> [resize]"


def resize_pixmap(img):
    img = pg.QtGui.QPixmap(fpath)
    iw = img.width()
    ih = img.height()
    print('original: ', iw, ih)
    if(iw==0) or (ih==0):
        return None
    ratio_w = WIDTH/iw
    ratio_h = HEIGHT/ih
    ratio = min(ratio_w, ratio_h)
    if (iw> WIDTH) or (ih > HEIGHT):
        w = int(ratio * iw)
        h = int(ratio * ih)
        print('resize: ', w, h)
        img = img.scaled(w, h)
# end
    return img
# end


class Window(pg.QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.setGeometry( PX, PY, WIDTH, HEIGHT)
# end

    def set_pixmap(self, pixmap):
        label = pg.QtWidgets.QLabel(self)
        iw = pixmap.width()
        ih = pixmap.height()
        x = (WIDTH - iw)//2
        y = (HEIGHT - ih)//2
        label.setGeometry(x, y, iw, ih)
        label.setPixmap(pixmap)
# end

    def set_fpath(self, fpath, is_resize):
        basename= os.path.basename(fpath)
        self.setWindowTitle(basename)
        pixmap = pg.QtGui.QPixmap(fpath)
        if is_resize:
            pixmap = resize_pixmap(pixmap)
# end
        if not pixmap:
            text = "cannot load " + basename
            print(text)
            return False
# end
        self.set_pixmap(pixmap)
        return True
# class end


def main(fpath, is_resize):
    app = pg.mkQApp()
    win = Window()
    win.set_fpath(fpath, is_resize)
    win.show()
    sys.exit(app.exec_())
# end


def usage(script):
    usage = USAGE_FORMAT.format(script)
    print(usage)
# end


# main
fpath = ""
is_resize = False
args = sys.argv
argc = len(args)
if argc < 2:
    usage(args[0])
    exit()
elif argc>= 3:
    fpath = args[1]
    is_resize = int(args[2])
elif argc>= 2:
    fpath = args[1]
# end
main(fpath, is_resize)

