# Python: transpose Image using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image


def transpose_image(fpath):
	name, ext = os.path.splitext(fpath)
	prefix = "pil_tutorial_image_transpose_"
	fname_rotate_180 = 	prefix  + "rotate_180_" + name + ext
	print(	fname_rotate_180)
	fname_rotate_270 = 	prefix + "rotate_270_"+ name + ext
	print(	fname_rotate_270)
	fname_rotate_90 = 	prefix  + "rotate_90_"+ name + ext
	print(	fname_rotate_90)
	fname_flip_left_right = 	prefix  + "flip_left_right_"+ name + ext
	print(	fname_flip_left_right)
	fname_flip_top_bottom = 	prefix  + "flip_top_bottom_"+ name + ext
	print(	fname_flip_top_bottom)
	fname_transpose = 	prefix  + "transpose_" + name + ext
	print(	fname_transpose)
	fname_transverse = prefix + "transverse_" + name + ext
	print(	fname_transverse)
	im = Image.open(fpath)
	im.transpose(Image.Transpose.ROTATE_180).save(	fname_rotate_180)
	im.transpose(Image.Transpose.ROTATE_270).save(	fname_rotate_270)
	im.transpose(Image.Transpose.ROTATE_90).save(	fname_rotate_90)
	im.transpose(Image.Transpose.FLIP_LEFT_RIGHT).save(	fname_flip_left_right)
	im.transpose(Image.Transpose.FLIP_TOP_BOTTOM).save(	fname_flip_top_bottom)
	im.transpose(Image.Transpose.TRANSPOSE).save(	fname_transpose)
	im.transpose(Image.Transpose.TRANSVERSE).save(	fname_transverse)
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
transpose_image(fpath)
