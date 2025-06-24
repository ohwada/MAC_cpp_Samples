# Python: show Anime gif  or Anime webp
# load gif file using QMovie
# show Anime using QLabel
#  2025-04-10  K.OHWADA

# https://pythonpyqt.com/pyqt-gif/


from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import sys, os


# Window
PX=50
PY=50
WIDTH = 480
HEIGHT = 360

USAGE_FORMAT = "Usage: python {:s}  <gif filepath>"


class Window(QMainWindow):
    def __init__(self):
        super(Window, self).__init__()
        self.setGeometry( PX, PY, WIDTH, HEIGHT)
        self.print_supportedFormats()
# end

    def print_supportedFormats(self):
        print('supportedFormats:')
        for f in QMovie.supportedFormats():
            print(f)
# end

    def set_fpath(self, fpath):
        basename= os.path.basename(fpath)
        self.setWindowTitle(basename)
        movie = QMovie(fpath)
        if not  movie.isValid():
            print('not valid')
            return False
# end
        img = QImage(fpath)
        iw = img.width()
        ih = img.height()
        print('width: ', iw )
        print('height: ', ih )
        print('format: ', movie.format() )
        print('frame count: ', movie.frameCount() )
        print('loop count: ', movie.loopCount() )
        x =  int((WIDTH - iw)//2)
        y =  int((HEIGHT - ih)//2)
        label = QLabel(self)
        label.setGeometry(x, y, iw, ih)
        label.setMovie(movie)
        movie.start()
        return True
# end


def main(fpath):
    app = QApplication(sys.argv)
    win = Window()
    win.set_fpath(fpath)
    win.show()
    sys.exit(app.exec_())


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


