#!/usr/bin/env python
#coding: utf-8


# convert id3tags encoding sjis to utf16
# 2020-03-01 K.OHWADA
# reference : https://abicky.net/2013/01/23/072137/
# reference :  https://note.nkmk.me/python-mutagen-mp3-id3/
# reference :  https://stackoverflow.com/questions/18248200/how-can-i-stop-mutagen-automatically-updating-the-id3-version
# reference :  https://stackoverflow.com/questions/18026516/how-to-set-artist-album-artist-year-album-song-number-and-title

import inspect
import eyed3
import eyed3.id3
from mutagen.id3 import ID3, COMM, TDRC, TYER
import shutil
import sys
import os

# main
backup = False

if (len(sys.argv) == 3):
    filepath = sys.argv[1]
    arg2 = int(sys.argv[2])
    if arg2 == 1:
        backup = True
elif (len(sys.argv) == 2):
    filepath = sys.argv[1]
else:
    print("\n Usage python3 %s <mp3File> [backup] " % sys.argv[0])
    exit()
# if

basename = os.path.basename(filepath)
fname = os.path.splitext(basename)[0]
filepath_tmp = fname + "_tmp.mp3"
filepath_utf16 = fname + "_utf16.mp3"

shutil.copyfile(filepath, filepath_tmp)
print('copy: ', filepath_tmp) 

# convert tags
audiofile = eyed3.load(filepath_tmp)
tag = audiofile.tag
if not tag:
    print("No tag")
    exit()
# if

print('tag version: ',  tag.version)

for prop, value in inspect.getmembers(tag):
    #if not isinstance(value, unicode):
    #continue
    try:
        # ID3 tag (encoded in cp932) is decoded in Latin-1 by 'decodeUnicode' function
        # note: don't specify 'shift_jis' because fails to decode platform dependent characters
        setattr(tag, prop, value.encode('latin1').decode('cp932'))
    except:
        pass
    # try

    version = tag.version
    if tag.isV1() or version == eyed3.id3.ID3_V2_2:
        version = (2, 3, 0)
    # if
# for

try:
    tag.save(encoding = 'utf-16', version = version, backup = backup)
except:
    # sometime fails to save tag due to using tags supported in ID3v2.4
    version = (2, 4, 0)
    tag.save(encoding = 'utf-16', version = version, backup = backup)
    print('saved version: ', version)
# try

print( 'converted: %s ' % filepath_tmp)

# update comment
shutil.copyfile(filepath_tmp, filepath_utf16)

# find comment
id3_tags = ID3(filepath_utf16)
has_comm = False
has_tdrc = False
for k, v in id3_tags.items():
    if 'COMM' in k:
        has_comm = True
        comm = v
    if 'TDRC' in k:
        has_tdrc = True
        tdrc = v
# for

# conv comment encoding
if has_comm:
    comm_list = comm.text
    comm_text = comm_list[0]
    comm_decode = comm_text.encode('latin1').decode('cp932')
    print('comm converted: ',  comm_decode)
    id3_tags[COMM] = COMM(encoding=3, text = comm_decode)
# if

# conv TRDC to TYER for v2.3.0
if has_tdrc:
    tdrc_list = tdrc.text
    tdrc_text = tdrc_list[0]
    id3_tags.add( TYER(encoding=3, text = str(tdrc_text)) )
# if

id3_tags.save(v2_version=3)

print( 'converted: %s ' % filepath_utf16)

