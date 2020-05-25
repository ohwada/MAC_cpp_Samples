#!/usr/bin/env python
#coding: utf-8

# add album picture if no picture
# reference : https://stackoverflow.com/questions/47346399/how-do-i-add-cover-image-to-a-mp3-file-using-mutagen-in-python/47346660#47346660

import mutagen
from mutagen.id3 import ID3, APIC
import sys
import os
import shutil

# main
if( len(sys.argv) != 3):
    print("\n Usage python3 %s <mp3File> <imgFile> " % sys.argv[0])
    exit()
# if

filepath_mp3 = sys.argv[1]
filepath_img = sys.argv[2]

basename_mp3 = os.path.basename(filepath_mp3)
fname_mp3 = os.path.splitext(basename_mp3)[0]
filepath_pic = fname_mp3 + '_pic.mp3';

basename_img = os.path.basename(filepath_img)
ext_img = os.path.splitext(basename_img)[1]

print('ext_img: ', ext_img)

if(ext_img == '.jpg'):
    img_mime = 'image/jpeg'
elif(ext_img == '.png'):
    img_mime = 'image/png'
# if

print('img_mime: ', img_mime)

shutil.copyfile(filepath_mp3, filepath_pic)

try:
    tags = ID3(filepath_pic)
except mutagen.id3.ID3NoHeaderError:
    print('ID3NoHeaderError')
    print('try add_new_tags.py')
    os.remove(filepath_pic)
    exit()
# try

if not tags:
    print('no tags')
    os.remove(filepath_pic)
    exit()
# if

if 'APIC' in tags:
    print('picture already exists')
    os.remove(filepath_pic)
    exit()
# if


img_data = open(filepath_img, 'rb').read()

tags.add(
    APIC(
       encoding=3, # 3 is for utf-8
        mime=img_mime, # image/jpeg or image/png
        type=3, # 3 is for the cover image
        desc='Cover',
        data=img_data
    )
)

#tags.save(filepath_pic)
tags.save(v2_version=3)
print('saved: ', filepath_pic)

