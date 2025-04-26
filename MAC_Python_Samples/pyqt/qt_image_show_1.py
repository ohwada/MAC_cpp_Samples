# Python: show image file using   PyQt5
# suport jpeg
# Not resize image
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
WIDTH=400
HEIGHT=400


def window(fpath):
    app = QApplication(sys.argv)
    win = QWidget()
    label = QLabel()
    pixmap = QPixmap(fpath)
    label.setPixmap(pixmap)
    vbox = QVBoxLayout()
    vbox.addWidget(label)
    win.setLayout(vbox)
    fname = os.path.basename(fpath)
    win.setWindowTitle(fname)
    win.setGeometry(PX, PY, WIDTH, HEIGHT)
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

