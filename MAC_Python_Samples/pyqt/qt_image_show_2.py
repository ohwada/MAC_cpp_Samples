# Python: show image file using   PyQt5
# the object oriented solution of qt_image_show1.py
# suport jpeg
# resize image
#  2025-04-10  K.OHWADA

# https://yamamon1010.hatenablog.jp/entry/qlabel_resize_image

import sys
import os
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QVBoxLayout
from PyQt5.QtGui import QPixmap

# Window
PX=10
PY=10
WIDTH = 400
HEIGHT = 400

class ImageViewer(QWidget):
    def __init__(self):
       super().__init__()
       self._init_ui()
# end

    def _init_ui(self):
       self.setGeometry(PX, PY, WIDTH,HEIGHT)
       layout = QVBoxLayout()
       self.title = QLabel()
       self.image = QLabel()
       layout.addWidget(self.image)
       self.setLayout(layout)
# end

    def set_fpath(self, fpath):
        fname = os.path.basename(fpath)
        self.setWindowTitle(fname)
        pixmap = QPixmap(fpath)
        pixmap_resize = pixmap.scaled(WIDTH, HEIGHT, Qt.KeepAspectRatio,Qt.FastTransformation)
        self.image.setPixmap(pixmap_resize)
        self.show()
# end

def main(fpath):
    app = QApplication(sys.argv)
    win = ImageViewer()
    win .set_fpath(fpath)
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
main(fpath)





