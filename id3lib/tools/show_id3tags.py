#!/usr/bin/env python
#coding: utf-8


# show id3 tags in mp3 file
# 2020-03-01 K.OHWADA
# original : https://github.com/nkmk/mutagen-example/blob/95e1408ba2d1c625c62b900980da9bf0ee666520/easyid3_example.py#L38-L40

from mutagen.easyid3 import EasyID3
from mutagen.id3 import ID3
import eyed3

import sys

# getComment
def getComment(filenane):
    id3_tags = ID3(filenane)
    for k, v in id3_tags.items():
        if "COMM" in k:
            return (v.text)[0]
        # if
    # for
# def ----


# main

if( len(sys.argv) != 2):
    print("\n Usage python3 %s <mp3File>" % sys.argv[0])
    exit()
#---

filenane = sys.argv[1]

audiofile = eyed3.load(filenane)
tag = audiofile.tag
if not tag:
    print("eyed3.load No tag")
    exit()
# if

print('tag version: ',  tag.version)

easy_tags = EasyID3(filenane)

print()
print(easy_tags.pprint())

id3_tags = ID3(filenane)
has_comm = False
for k, v in id3_tags.items():
    if "COMM" in k:
        has_comm = True
        comm = v
    # if
# for

if has_comm: 
    comm_text = (comm.text)[0]
    print ('comment: ', comm_text)
else:
    print ('no comment ')
# if

print()

