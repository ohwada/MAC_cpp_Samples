# Python: load Image file using QImage
# convert QImage to Pillow Image
# show Image using Pillow Image 
# 2025-04-10  K.OHWADA


from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PIL import Image
import io
import sys

SAVE_FORMAT = "BMP"

USAGE_FORMAT = "Usage: python {:s}  <image filepath>"

# https://doloopwhile.hatenablog.com/entry/20100305/1267782841
def qimage2pilimage(qimage):
    buffer = QBuffer()
    buffer.open(QIODevice.WriteOnly)
    qimage.save(buffer, SAVE_FORMAT)
    fp = io. BytesIO()
    fp.write(buffer.data().data())
    buffer.close()
    fp.seek(0)
    return Image.open(fp)
# end


def show_image(fpath):
	qimg = QImage(fpath)
	pimg = qimage2pilimage(qimg)
	pimg.show()
# end

def usage(script):
	usage = USAGE_FORMAT.format(script)
	print(usage)
# end

# main
args = sys.argv
argc = len(args)
if argc < 2:
	usage( args[0])
	exit()
# end
show_image( args[1])  
