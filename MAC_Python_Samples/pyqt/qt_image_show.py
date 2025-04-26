# Python: show image file using   PyQt5
# suport jpeg
#  2025-04-10  K.OHWADA

# https://qiita.com/hoshianaaa/items/05791e6518f26bca50d7

import sys
import os
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

# Window
PX=10
PY=10
WIDTH=300
HEIGHT=300


def window(fpath):
    app = QApplication(sys.argv)
    win = QWidget()
    l1 = QLabel()
    pixmap = QPixmap(fpath)
    w = win.width()
    h = win.height()
    pixmap_resize = pixmap.scaled(w, h, Qt.KeepAspectRatio,Qt.FastTransformation)
    l1.setPixmap(pixmap_resize)
    vbox = QVBoxLayout()
    vbox.addWidget(l1)
    win.setLayout(vbox)
    fname = os.path.basename(fpath)
    win.setWindowTitle(fname)
    win.setGeometry(PX, PY, WIDTH,HEIGHT)
    win.show()
    sys.exit(app.exec_())
# end

# main
args = sys.argv
argc = len(args)
script = args[0]

if argc < 2:
	print("Usage: python %s  <image filepath>" % script)
	exit()
# end

fpath = args[1]
window(fpath)

