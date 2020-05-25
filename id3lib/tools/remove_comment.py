#!/usr/bin/env python
#coding: utf-8


# remove comment tag 
# 2020-03-01 K.OHWADA
# reference :  https://mutagen.readthedocs.io/en/latest/api/id3.html


from mutagen.id3 import ID3, COMM
import sys
import os
import shutil

# main
if (len(sys.argv) != 2):
    print("\n Usage python3 %s <mp3File>  " % sys.argv[0])
    exit()
# if

filepath = sys.argv[1]

basename = os.path.basename(filepath)
fname = os.path.splitext(basename)[0]
filepath_remove = fname + "_remove.mp3"

shutil.copyfile(filepath, filepath_remove)

id3_tags = ID3(filepath_remove)

# find comment tag
has_comm = False
for k, v in id3_tags.items():
    if "COMM" in k:
        has_comm = True
# for

if not has_comm:
    print('no comment')
    exit()
# if

# remove comment
id3_tags.delall('COMM')
id3_tags.save()

print( 'removeed: %s ' % filepath_remove)

