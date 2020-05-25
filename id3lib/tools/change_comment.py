#!/usr/bin/env python
#coding: utf-8


# change comment tag
# 2020-03-01 K.OHWADA
# reference :  https://note.nkmk.me/python-mutagen-mp3-id3/

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
filepath_change = fname + "_change.mp3"

shutil.copyfile(filepath, filepath_change)

# find comment tag
id3_tags = ID3(filepath_change)

# find comment tag
has_comm = False
for k, v in id3_tags.items():
    if "COMM" in k:
        has_comm = True
        comm = v
# for

if not has_comm:
    print('no comment')
    exit()
# if

comm_text_list = comm.text
comm_text = = comm_text_list[0]

# change comment
id3_tags[COMM] = COMM(encoding=3, text='new comment')
id3_tags.save()

print( 'changed: %s ' % filepath_change)

