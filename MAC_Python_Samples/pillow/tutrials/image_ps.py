# Python: create PostScript file using Pillow
# 2025-04-10  K.OHWADA

# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html

import os, sys
from PIL import Image, PSDraw


# A4 size in points 
PAGE_WIDTH = 598
PAGE_HEIGHT = 842  

THUMBNAI_WIDTH = PAGE_WIDTH//2 - 100
THUMBNAI_HEIGHT  = PAGE_HEIGHT // 2

IMG_Y_MERGIN = 200

DPI = 75

# font
FONT_NAME = "Helvetica-Narrow-Bold"
FONT_SIZE = 36


def create_ps(fpath):
	name, ext = os.path.splitext(fpath)
	ps_fname = "pil_tutorial_image_ps_" + name + ".ps"
	print(	ps_fname)

# define the PostScript file
	ps_file = open(	ps_fname, "wb")

# Create a PSDraw object
	ps = PSDraw.PSDraw(ps_file)

# Start the document
	ps.begin_document()

# Set the text to be drawn
	text = name

# Calculate text size (approximation as PSDraw doesn't provide direct method)
# Assuming average character width as 0.6 of the font size
	text_width = len(text) * FONT_SIZE * 0.6
	text_height = FONT_SIZE

# Set the position (top-center)
	text_x = (  PAGE_WIDTH - text_width) // 2
	text_y =   PAGE_HEIGHT - text_height - 50  # Distance from the top of the page

# Load the image
	with Image.open(fpath) as im:
		im = im.convert("RGB") # for png

    # Resize the image if it's too large
		img_width = THUMBNAI_WIDTH
		img_height  = THUMBNAI_HEIGHT

		if (im.width > PAGE_WIDTH//2):
			img_width = im.width//3
			img_height = im. height//3
# end

		size = (img_width,  img_height)
		im.thumbnail(size)

    # Define the box where the image will be placed
		img_x = (  PAGE_WIDTH - img_width) //2
		img_y = text_y + text_height - (img_height//2) - IMG_Y_MERGIN  # 200 points below the text

    # Draw the image (75 dpi)
		ps.image((img_x, img_y, img_x + img_width, img_y + img_height), im, DPI)

# Draw the text
		ps.setfont(FONT_NAME, FONT_SIZE)
		ps.text((text_x, text_y), text)

# End the document
		ps.end_document()
# with end
	ps_file.close()
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
create_ps(fpath)

