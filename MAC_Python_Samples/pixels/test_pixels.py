 # test for  pixels.py
# show  Pixels as Image using matplotlib
# save Pixels to png file using Pillow
 # 2025-04-10 K.OHWADA
 
from pixels import Pixels
from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
import sys, os


# hide all axis labels
AXIS = "off"

COLOR_MATRIX_NAME_FORMAT ="ColorMatrix_{:d}x{:d}_{:d}"

CHECKER_BOARD_NAME_FORMAT = "CheckerBoard_{:d}x{:d}_{:d}"

USAGE_FORMAT = """
Usage: python {:s}  <num> <scale>
num:
2: 2x2 Color Matrix
3: 3x3  Color Matrix
4: 4x4  Color Matrix
8: 8x8 Checker Board Pattern
"""


def show_pixels( pixels, name):
    np_arr = np.array(pixels)
    plt.figure(num= name)
    plt.axis(AXIS )
    plt.imshow(np_arr)
    plt.show()
# end


def save_pixels( pixels, name):
    outfile = "pixels_" + name +".png"
    np_arr = np.array(pixels, dtype=np.uint8)
    img = Image.fromarray(  np_arr,  mode="RGB")
    img.save(outfile)
    print('save ', outfile)
# end


def show_save_pixels( pixels, name):
    save_pixels( pixels, name)
    show_pixels( pixels, name)
# end


def show_save_colorMatrix(num, scale):
    name = COLOR_MATRIX_NAME_FORMAT.format(num, num, scale)
    print(name)
    pixels = Pixels.createColorMatrixPixels(num, scale)
    show_save_pixels( pixels, name)
# end


def show_save_checkerBoard(num, scale):
    name= CHECKER_BOARD_NAME_FORMAT.format(num, num, scale)
    print(name)
    pixels = Pixels.createCheckerBoardPixels(num, scale)
    show_save_pixels( pixels, name)
# end


def usage(script):
    usage = USAGE_FORMAT.format(script)
    print(usage)
# end


# main
args = sys.argv
argc = len(args)
if argc < 3:
    usage(args[0])
    exit()
# end
num = int(args[1])
scale = int(args[2])
print(num, scale)
if (num >= 2) and (num <= 4) :
    show_save_colorMatrix(num, scale)
else:
    show_save_checkerBoard(num, scale)
# end

