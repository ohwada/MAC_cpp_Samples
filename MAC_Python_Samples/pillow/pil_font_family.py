# Python: get font family from font file using Pillow
# 2025-04-10  K.OHWADA

# https://nakamura001.hatenablog.com/entry/20101228/1293508002

from PIL import ImageFont, ImageDraw
import sys

FONT_PATH = "Times.ttc"  
# FONT_PATH =  "/System/Library/FontsApple Color Emoji.ttc" # OSError

print('font: ', FONT_PATH)
f = ImageFont.truetype(FONT_PATH)
print ('family:',f.font.family)
familyName, fontName = f.getname()
print ('familyName:',familyName)
print ('fontName:',fontName)

