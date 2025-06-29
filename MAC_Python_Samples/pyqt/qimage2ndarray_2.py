# Python: load Image file using QImage
 # convet QImage to numpy ndarray
# show Image using matplotlib
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtGui import *
import matplotlib.pyplot as plt
import numpy as np
import sys, os

AXIS = "off"

USAGE_FORMAT = "Usage: python {:s}  <image filepath>"

# https://medium.com/@bgallois/numpy-ndarray-qimage-beware-the-trap-52dcbe7388b9
def qimage2ndarray(qimg):
 # png : 5 ARGB32, jpg: 4  RGB32
	qimg_format = qimg.format()
	print('image format: ', qimg_format)
	width = qimg.width()
	height = qimg.height()
	byte_count = qimg.byteCount()
	bytes_per_line = qimg.bytesPerLine()
	ch = int( bytes_per_line/width )
	bits_size = width * height * ch
	print('width: ', width)
	print('height: ', height)
	print('byte_count:', byte_count)
	print('bytes_per_line: ', bytes_per_line)
	print('ch: ', ch)
	print('bits_size: ', bits_size)
	bits = qimg.constBits()
	bits.setsize(bits_size)
	np_arr = np.array(bits, np.uint8).reshape((height, width, ch))
# magic: this conversion works well
	arr = np_arr[:, :, [2, 1, 0, 3]] # g(2), r(1), a(0), b(3)
	return arr
# end


def show_ndarray(ndarray, name):
	plt.figure(num=name)
	plt.axis(AXIS)
	plt.imshow(ndarray)
	plt.show()
# end


def show_image(fpath):
	basename = os.path.basename(fpath)
	qimg = QImage(fpath)
	ndarray = qimage2ndarray(qimg)
	show_ndarray(ndarray, 	basename)
# end

def usage(script):
	usage = USAGE_FORMAT.format(script)
	print(usage)

# main
args = sys.argv
argc = len(args)
if argc < 2:
	usage(args[0])
	exit()
# end
show_image(args[1])
