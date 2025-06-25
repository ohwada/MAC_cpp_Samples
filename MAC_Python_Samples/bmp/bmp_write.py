 # save Color Matrix Pixels to BMP file 
 # 2025-04-10 K.OHWADA
 
from bmp import Bmp
from pixels import Pixels
import matplotlib.pyplot as plt
import numpy as np
import sys, os

SIZE = 256

# hide all axis labels
AXIS = "off"

USAGE_FORMAT = """
Usage: python {:s}  <num>
2: 2x2 Color Matrix
3: 3x3 Color Matrix
4: 4x4 Color Matrix
8: 8X8 Checker Board Pattern
"""


def show_img(pixels, name):
    np_arr = np.array(pixels)
    plt.figure(num=name)
    plt.axis(AXIS )
    plt.imshow(np_arr)
    plt.show()
# end


def write_bmp(width, height, pixels, name):
    outfile = name + ".bmp"
    print(outfile)
    bmp = Bmp()
    bmp.setPixels(width, height, pixels)
    bmp.writeFile(outfile)
    bmp.printHeader()
# end


def show_save_colorMatrix(num):
    scale = int(SIZE / num)
    size = num * scale
    name =  "ColorMatrix_" + str(num) + "x" +  str(num)
    print(name)
    pixels = Pixels.createColorMatrixPixels(num, scale)
    write_bmp(size, size, pixels, name)
    show_img(      pixels, name)
# end

def show_save_checkerBoard_8x8():
    scale = int(SIZE /8)
    size = 8 * scale
    name =  "CheckerBoard_8x8"
    print(name)
    pixels = Pixels.createCheckerBoardPixels(8, scale)
    write_bmp(size, size, pixels, name)
    show_img(pixels, name)
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
# end
num = int(args[1])
if (num>=2) and (num<=4) :
    show_save_colorMatrix(num)
elif num==8:
    show_save_checkerBoard_8x8()
# end


