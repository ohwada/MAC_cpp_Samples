# Python: load Imge file and Image using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image, ImageOps

SIZE = (100, 150)

def image_ops(fpath):
	name, ext = os.path.splitext(fpath)
	prefix =  "pil_tutorial_image_ops_"
	fname_contain = prefix + "contain_" + name + ext
	print(fname_contain)
	fname_cover = prefix  + "cover_"+name + ext
	print(fname_cover)
	fname_fit = prefix  + "fit_" +name + ext
	print(fname_fit)
	fname_pad = prefix  + "pad_" +name + ext
	print(fname_pad)
	fname_thumbnail = prefix + "thumbnail_"  +name + ext
	print(fname_thumbnail)	
	with Image.open(fpath) as im:
		ImageOps.contain(im, SIZE).save(fname_contain)
		ImageOps.fit(im, SIZE).save(fname_fit)
		ImageOps.pad(im, SIZE, color="#f00").save(	fname_pad)

# AttributeError: module 'PIL.ImageOps' has no attribute 'cover'
		# ImageOps.cover(im, SIZE).save(fname_cover)

    # thumbnail() can also be used,
    # but will modify the image object in place
		im.thumbnail(SIZE)

		im.save(fname_thumbnail)
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
image_ops(fpath)
