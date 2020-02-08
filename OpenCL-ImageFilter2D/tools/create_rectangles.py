#!/usr/bin/env python

# create image file rectangles.png
# 2020-01-01 K.OHWADA

import sys
import os
import random
from PIL import Image, ImageDraw

BLACK = (0, 0, 0)
WHITE = (256, 256, 256)
RED = (256, 0, 0);
BLUE = (0, 0, 256);

im = Image.new('RGB', (512, 512), WHITE)
draw = ImageDraw.Draw(im)

x1 = 200
y1 = 200
x2 = 210
y2 = 210

for i in range(10):
    x1 -= 4; 
    y1 -= 4; 
    x2 += 4;
    y2 += 4;

    # red
    draw.line((x1, y1, x2, y1), fill=RED, width=1)
    draw.line((x2, y1, x2, y2), fill=RED, width=1)
    draw.line((x2, y2, x1, y2), fill=RED, width=1)
    draw.line((x1, y2, x1, y1), fill=RED, width=1)

    # blue
    draw.line((x1, y1+100, x2, y1+100), fill=BLUE, width=1)
    draw.line((x2, y1+100, x2, y2+100), fill=BLUE, width=1)
    draw.line((x2, y2+100, x1, y2+100), fill=BLUE, width=1)
    draw.line((x1, y2+100, x1, y1+100), fill=BLUE, width=1)

    # black
    draw.line((x1, y1+200, x2, y1+200), fill=BLACK, width=1)
    draw.line((x2, y1+200, x2, y2+200), fill=BLACK, width=1)
    draw.line((x2, y2+200, x1, y2+200), fill=BLACK, width=1)
    draw.line((x1, y2+200, x1, y1+200), fill=BLACK, width=1)

output = 'rectangles.png'
im.save(output)
print("created: " + output)

