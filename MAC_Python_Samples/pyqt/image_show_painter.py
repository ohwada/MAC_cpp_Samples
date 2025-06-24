# Python: load Image file using QPixmap
# draw Image using QPainter
# If Image is smaller than Window, show Image in original size
# If Image is large than Window, show Image in resized size
 # suport jpeg
#  2025-04-10  K.OHWADA


from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import sys, os


# Window
PX = 50
PY = 50
WIDTH = 480
HEIGHT = 360

# Font
FONT_FAMILY = "Arial"
FONT_SIZE = 32

ERROR_STYLE ="QLabel { color : red;}"

USAGE_FORMAT = "Usage: python {:s}  <image filepath>"


def resize_image(fpath):
    img = QPixmap(fpath)
    iw = img.width()
    ih = img.height()
    if (iw == 0) or (ih == 0):
        print("cannot load image: ", fpath)
        return None
# end
    print('original: ', iw, ih)
    if (iw> WIDTH) or (ih > HEIGHT):
        width = int(0.9 * WIDTH)
        height = int(0.9 * HEIGHT)
        img = img.scaled(width, height, Qt.KeepAspectRatio,Qt.FastTransformation)
        w = img.width()
        h = img.height()
        print('resize:', w, h)
# end
    return img
# end


def set_text(win, text):
    x = 2 *  FONT_SIZE
    y = 2 *  FONT_SIZE
    w = (len(text) + 2) * FONT_SIZE
    h = int(1.5 * FONT_SIZE)
    label = QLabel(win)
    font = QFont()
    font.setFamily(FONT_FAMILY)
    font.setPointSize(  FONT_SIZE)
    label.setFont(font)
    label.setGeometry(x, y, w, h)
    label.setStyleSheet(ERROR_STYLE)
    label.setText(text)
# end


class Window(QMainWindow):
    def __init__(self):
        super(Window, self).__init__()
        self.setGeometry( PX, PY, WIDTH, HEIGHT)
# end

    def set_fpath(self,fpath):
        basename= os.path.basename(fpath)
        self.setWindowTitle(basename)
        pixmap = resize_image(fpath)
        if not pixmap:
            text = "cannot load " + basename
            set_text(self, text)
            return False
# end
        self.setWindowTitle(basename)
        self.pixmap = pixmap
        self.update
        return True
# def end

    def paintEvent(self, event):
        w = self.width()
        h = self.height()
        iw = self.pixmap.width()
        ih = self.pixmap.height()
        x= int ((w - iw)//2)
        y= int( (h - ih)//2 )
        qp = QPainter()
        qp.begin(self)
        qp.drawPixmap(x, y, self.pixmap)
        qp.end()
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
