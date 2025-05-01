# Python: draw text using Pillow
# 2025-04-10  K.OHWADA

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

#  Image
MODE = "RGB"

WIDTH = 200
HEIGHT = 200

BG_COLOR = (256, 256, 256) # white

# Text
TEXT = "Hello,World!"                   

TEXT_COLOR = (0, 0, 0, 255) # black

FNAME = "pil_text.png"

                        
# main
img = Image.new(MODE, (WIDTH,  HEIGHT), BG_COLOR)

draw = ImageDraw.Draw(img)

imgWhidth, imgHight = img.size 

textWidth = draw.textlength(TEXT)
                
x = (imgWhidth - textWidth) // 2      
y = imgHight // 2
  
draw .text((x, y), TEXT, TEXT_COLOR)

img.show()

img.save(FNAME)               
