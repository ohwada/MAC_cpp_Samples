# Python: play Sound using QSound
# wav only, Not support mp3
# 2025-04-10  K.OHWADA

# https://www.wizard-notes.com/entry/python/pyqt-qsound


from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtMultimedia import *
import sys, time


USAGE_FORMAT = "Usage: python {:s}  <sound filepath>"


def play_sound(fpath):
    app = QApplication(sys.argv)
    sound = QSound(fpath)
    sound.play() 
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
play_sound(args[1])
