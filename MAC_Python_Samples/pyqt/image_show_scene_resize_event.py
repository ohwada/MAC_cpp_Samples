# Python: 
# Python: load Image file using QPixmap
# show Image using QGraphicsScene
# automatically change Image Size when Window  (Canvas) is resized
# When Image smaller then Window, Image is original size
# When Image is large than Window, resize Image to fit Window
#  2025-04-10  K.OHWADA

# https://yamamon1010.hatenablog.jp/entry/qlabel_resize_image

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import sys, os


# Window
PX = 50
PY = 50
WIDTH = 480
HEIGHT = 360

USAGE_FORMAT = "Usage: python {:s}  <image filepath>"


class Canvas(QWidget):
    def __init__(self):
        super(Canvas, self).__init__()
        self.layout = QGridLayout()
        self.setLayout(self.layout)
        self.view = QGraphicsView()  
        self.layout.addWidget(self.view)
        self.pixmap_orig = QPixmap()
        self.is_load = False
# end

    def set_fpath(self, fpath):
        img = QPixmap(fpath)
        iw = img.width()
        ih = img.height()
        if (iw == 0) or (ih == 0):
            print("cannot load image: ", fpath)
            return None
# end
        print('original: ', iw, ih)
        self.pixmap_orig = img
        self.is_load = True
        return True
# end        


    def resize_image(self, win_width, win_height): 
        img = self.pixmap_orig
        iw = img.width()
        ih = img.height()
    # prevent zero division
        if (iw == 0) or (ih ==0):
            print('pixmap: ', iw, ih)
            return None
# if end
        width = int(0.9*win_width)
        height = int(0.9*win_height)
        print('win: ', win_width, win_height)
        print('win liit: ', width, height)
    # Image is large than Window
        if ( iw > width ) or ( ih > height):
            img = img.scaled(width, height, Qt.KeepAspectRatio,Qt.FastTransformation)
            iw = img.width()
            ih = img.height()
            print('resize: ', iw, ih)
	# if end
        return img
# def end


    def resizeEvent(self, event):
        if not self.is_load:
            return
# if end
        width = self.width()
        height = self.height()
        pixmap = self.resize_image(width, height)
        self.view.resetCachedContent()
        scene = QGraphicsScene()
        scene.addPixmap(pixmap)
        self.view.setScene(scene)
# end


class Window(QMainWindow):
    def __init__(self):
        super(Window, self).__init__()
        self.canvas = Canvas()
        self.setCentralWidget(self.canvas)
        self.setGeometry( PX, PY, WIDTH, HEIGHT)
# end

    def set_fpath(self,fpath):
        fname = os.path.basename(fpath)
        self.setWindowTitle(fname)
        self.canvas.set_fpath(fpath)
#end


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
