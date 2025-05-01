# Python: draw text in Japanese using Pillow
# 2025-04-10  K.OHWADA

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
import os


# Font
FONT_NAME = "AppleSDGothicNeo.ttc" # Mac

# FONT_NAME = "Times.ttc"   # Not Japanes 

FONT_SIZE = 36  

#  Image
MODE = "RGB"

WIDTH = 300

HEIGHT = 300

BG_COLOR = (256, 256, 256) # white

# Text
TEXT = "Hello,World!"                   

TEXT_JP = "こんにちわ 世界"   

TEXT_COLOR = (0, 0, 0, 255) # black

# Save
FNAME = "pil_font_jp.png"

                       

# main
img = Image.new(MODE, (WIDTH,  HEIGHT), BG_COLOR)

draw = ImageDraw.Draw(img)

fnt = ImageFont.truetype(FONT_NAME, FONT_SIZE)

imgWhidth, imgHight = img.size 
      
textWidth = draw.textlength(TEXT, font=fnt)
       
x1 = (imgWhidth - textWidth) // 2      
y1 = (imgHight - FONT_SIZE) // 2       #

draw .text((x1, y1), TEXT, TEXT_COLOR, font=fnt)

textWidthJp = draw.textlength(TEXT_JP, font=fnt)
       
x2 = (imgWhidth - textWidthJp) // 2      
y2 = y1 + int(1.5 * FONT_SIZE  )    #

draw .text((x2, y2), TEXT_JP, TEXT_COLOR, font=fnt)

img.show()

name = os.path.splitext( os.path.basename(FONT_NAME) )[0]

fname = "pil_font_jp_" + name + ".png"

print(fname)

img.save(fname)  
             
