# Python: show image file using   PyQt5
# suport jpeg
#  2025-04-10  K.OHWADA

# https://yamamon1010.hatenablog.jp/entry/qlabel_resize_image

import sys

from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QVBoxLayout
from PyQt5.QtGui import QPixmap

class ImageViewer(QWidget):
   def __init__(self):
       super().__init__()
       self.width = 512
       self.height = 512
       self._init_ui()

   def _init_ui(self):
       self.resize(self.width,self.height)
       layout = QVBoxLayout()
       self.title = QLabel()
       self.image = QLabel()
       layout.addWidget(self.image)
       self.setLayout(layout)
       pixmap = QPixmap('sample.png')
       pixmap = pixmap.scaled(self.width, self.height, Qt.KeepAspectRatio,Qt.FastTransformation)
       self.image.setPixmap(pixmap)
       self.show()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    widget = ImageViewer()
    sys.exit(app.exec_())




