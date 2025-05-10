# Python: Image Filter using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image, ImageFilter


def image_filter(fpath):
	name, ext = os.path.splitext(fpath)
	prefix =  "pil_tutorial_image_filter_"
	fname_detail =  prefix  + "detail_" + name+ ext
	print(fname_detail)
	fname_blur = prefix  + "blur_" + name + ext
	print(fname_blur)
	fname_contour = prefix + "contour_"  + name + ext
	print(fname_contour)
	fname_edge_enhance =  prefix + "edge_enhance_" + name + ext
	print(fname_detail)
	fname_edge_enhance_more = prefix  + "edge_enhance_more_"+ name  + ext
	print(fname_edge_enhance_more)
	fname_emboss = prefix  + "emboss_ "+ name + ext
	print(fname_emboss)
	fname_find_edges = prefix + "find_edges_"  + name + ext
	print(fname_find_edges)
	fname_sharpen = prefix  + "sharpen_" + name + ext
	print(fname_sharpen)
	fname_smooth = prefix + "smooth_" + name + ext
	print(fname_smooth)
	fname_smooth_more = prefix + "smooth_more_"  + name   + ext
	print(fname_smooth_more)
	im = Image.open(fpath)
	im.filter(ImageFilter.DETAIL).save(fname_detail)
	im.filter(ImageFilter.BLUR).save(fname_blur)
	im.filter(ImageFilter.CONTOUR).save(fname_contour)
	im.filter(ImageFilter.EDGE_ENHANCE).save(fname_edge_enhance)
	im.filter(ImageFilter.EDGE_ENHANCE_MORE).save(fname_edge_enhance_more)
	im.filter(ImageFilter.EMBOSS).save(fname_emboss)
	im.filter(ImageFilter.FIND_EDGES).save(fname_find_edges)
	im.filter(ImageFilter.SHARPEN).save(fname_sharpen)
	im.filter(ImageFilter.SMOOTH).save(fname_smooth)
	im.filter(ImageFilter.SMOOTH_MORE).save(fname_smooth_more)
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
image_filter(fpath)
