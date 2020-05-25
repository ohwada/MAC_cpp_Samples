#!/usr/bin/env python
#coding: utf-8


# convert id3tags version to v2.3.0
# 2020-03-01 K.OHWADA
# reference :  https://stackoverflow.com/questions/18248200/how-can-i-stop-mutagen-automatically-updating-the-id3-version

from mutagen.id3 import ID3
import shutil
import sys
import os

# main
if (len(sys.argv) != 2):
    print("\n Usage python3 %s <mp3File> [backup] " % sys.argv[0])
    exit()
# if

filepath = sys.argv[1]

basename = os.path.basename(filepath)
fname = os.path.splitext(basename)[0]
filepath_v230 = fname + "_v230.mp3"


shutil.copyfile(filepath, filepath_v230)

 
# update tags
tags = ID3(filepath_v230)
if not tags:
    print("No tags")
    exit()
# if

tags.save(v2_version=3)

print( 'converted: %s ' % filepath_v230)

