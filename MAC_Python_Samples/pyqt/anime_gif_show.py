# Python: show Anime gif 
#file  load Anime gif using QMovie
# show Anime gif  using QLabel
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

LABEL_X = 10
LABEL_Y = 10

USAGE_FORMAT = "Usage: python {:s}  <movie filepath>"


class Window(QMainWindow):
    def __init__(self):
        super(Window, self).__init__()
        self.setGeometry( PX, PY, WIDTH, HEIGHT)
# end

    def set_fpath(self, fpath):
        basename= os.path.basename(fpath)
        self.setWindowTitle(basename)
        w = int(0.9 * WIDTH)
        h = int(0.9 * HEIGHT)
        label = QLabel(self)
        label.setGeometry( LABEL_X, LABEL_Y, w, h)
        movie = QMovie(fpath)
        if not  movie.isValid():
            print('not valid')
            return False
# end
        print('format: ', movie.format() )
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


