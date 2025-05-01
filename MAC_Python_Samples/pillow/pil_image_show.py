# Python: show Image file using Pillow 
# suport jpeg
# disply Image in original size on Preview app
# 2025-04-10  K.OHWADA

# https://www.kikagaku.co.jp/kikagaku-blog/pillow/#i-3

from PIL import Image
import sys


def show_image(fpath):
	img = Image.open(fpath)
	img.show()
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
show_image(fpath)