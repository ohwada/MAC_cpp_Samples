# Python: play Music using  QMediaPlayer
# support mp3
# 2025-04-10  K.OHWADA


from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtMultimedia import *
import sys, os


ERROR_FORMAT  = "Error: {:s} : {:s}" 

USAGE_FORMAT = "Usage: python {:s}  <music filepath>"


def play_music(fpath):
    global player, basename
    basename = os.path.basename(fpath)
    print('basename:', basename)
    app = QApplication(sys.argv)
    url = QUrl.fromLocalFile(fpath)
    print(url)
    media =  QMediaContent(url)
    print(media)
    player = QMediaPlayer()
    player.error.connect(handleError)
    player.setMedia(media)
    player.play() 
    sys.exit(app.exec_())
# end

def handleError(self):
    global player, basename
    text = ERROR_FORMAT.format(player.errorString(), basename)
    print(text)
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
fname = args[1]
abspath = os.path.abspath(__file__)
print('abspath: ', abspath)
dir = os.path.dirname(abspath)
print('dir: ', dir)
fpath = os.path.join(dir, fname)
play_music(fpath)

