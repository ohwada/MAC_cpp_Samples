#!/usr/bin/env python

# clop Image
# 2020-01-01 K.OHWADA


import sys
import os
from PIL import Image

args = sys.argv

if (len(args) <2 ):
    print("Usage: " + args[0] + " <imageFileName> ")
    exit()

input = args[1]

basename = os.path.basename(input)
title, ext = os.path.splitext(basename)
output = title + "_crop" + ext

im = Image.open(input)

# for OpenCL_Logo.png
im_crop = im.crop((370, 540, 570, 660))

im_crop.save(output)
print("save to: " + output)

