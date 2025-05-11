# Python: draw Text inVertical writing using Pillow
# 2025-04-10  K.OHWADA

from PIL import Image, ImageDraw, ImageFont
import os


# Font
FONT_NAME = "AppleSDGothicNeo.ttc" # Mac

FONT_SIZE = 36  

#  Image
MODE = "RGB"

WIDTH = 300

BG_COLOR = (256, 256, 256) # white

# Text            
TEXT_JP = "こんにちわ 世界"   

TEXT_COLOR = (0, 0, 0, 255) # black

# middle top 
# https://pillow.readthedocs.io/en/stable/handbook/text-anchors.html#text-anchors
ANCHOR ="mt"

# top to bottom
# https://pillow.readthedocs.io/en/stable/reference/ImageDraw.html#PIL.ImageDraw.ImageDraw.text
DIRECTION ="ttb"
  
                  
# main
height = ( len(TEXT_JP) + 1 ) *  int(1.5 * FONT_SIZE  )

print(height)

img = Image.new(MODE, (WIDTH,  height), BG_COLOR)

draw = ImageDraw.Draw(img)

fnt = ImageFont.truetype(FONT_NAME, FONT_SIZE)

imgWhidth, imgHight = img.size 
      
x = imgWhidth// 2 
     
y = FONT_SIZE

draw .text((x, y), TEXT_JP, TEXT_COLOR, font=fnt, anchor= ANCHOR, direction=DIRECTION)

img.show()

name = os.path.splitext( os.path.basename(FONT_NAME) )[0]

fname = "pil_text_ttb_" + name + ".png"

print(fname)

img.save(fname) 
 
             
