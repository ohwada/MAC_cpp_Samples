# Python: draw Text Outline using Pillow
# 2025-04-10  K.OHWADA

from PIL import Image, ImageDraw, ImageFont
import os

# Font
FONT_NAME = "Times.ttc"  

FONT_SIZE = 36  

#  Image
MODE = "RGB"

WIDTH = 300
HEIGHT = 300

BG_COLOR = (256, 256, 256) # white

# Text
TEXT = "Hello,World!"                   

TEXT_COLOR = (256, 256, 256) # white

STROKE_WIDTH =2

STROKE_FILL = (0, 0, 0) # black 


# main
img = Image.new(MODE, (WIDTH,  HEIGHT), BG_COLOR)

draw = ImageDraw.Draw(img)

fnt = ImageFont.truetype(FONT_NAME, FONT_SIZE)

imgWhidth, imgHight = img.size 
      
textWidth = draw.textlength(TEXT, font=fnt)
       
x = (imgWhidth - textWidth) // 2      
y = (imgHight - FONT_SIZE) // 2       #

draw .text((x, y), TEXT, TEXT_COLOR, font=fnt, stroke_width=STROKE_WIDTH, stroke_fill= STROKE_FILL)

img.show()

name = os.path.splitext( os.path.basename(FONT_NAME) )[0]

fname = "pil_text_stroke_" + name + ".png"

print(fname)

img.save(fname)  

             
