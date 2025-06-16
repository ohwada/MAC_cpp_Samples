# Python: play Movie
#f load  # Python: play Movie file using QMediaPlayer
# play # Python: play Movie  using QVideoWidget
#  2025-04-10  K.OHWADA


from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtMultimedia import *
from PyQt5.QtMultimediaWidgets import *
import sys, os


# Window
PX=50
PY=50
WIDTH = 480
HEIGHT = 360

LABEL_X = 10
LABEL_Y = 10

USAGE_FORMAT = "Usage: python {:s}  <movie filepath>"

ERROR_FORMAT  = "Error: {:s} : {:s}" 


class Window(QMainWindow):
    def __init__(self):
        super(Window, self).__init__()
        self.setGeometry( PX, PY, WIDTH, HEIGHT)
        self.initPlayer()
# end

    def initPlayer(self):
        videoWidget = QVideoWidget()
        self.player = QMediaPlayer(None, QMediaPlayer.VideoSurface)
        self.player.setVideoOutput(videoWidget)
        self.player.error.connect(self.handleError)
        self.setCentralWidget(videoWidget)
# end

    def set_fpath(self, fpath):
        self.basename = os.path.basename(fpath)
        self.setWindowTitle(self.basename)
        media = QMediaContent(QUrl.fromLocalFile(fpath))
        self.player.setMedia(media)
        self.player.play()
# end

    def handleError(self):
        text = ERROR_FORMAT.format(self.player.errorString(), self.basename)
        print(text)
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
fname = args[1]
abspath = os.path.abspath(__file__)
print('abspath: ', abspath)
dir = os.path.dirname(abspath)
print('dir: ', dir)
fpath = os.path.join(dir, fname)
main(fpath)


