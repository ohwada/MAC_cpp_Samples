#!/usr/bin/env python
#coding: utf-8

# recover album picture in mp3 file
# some files do not have SOI
# 2020-03-01 K.OHWADA

# reference : https://www.programcreek.com/python/example/73822/mutagen.id3.APIC


from mutagen.id3 import ID3, APIC
from PIL import Image
import io 
import sys
import os
import shutil


# main
SOI = bytes([0xFF, 0xD8, 0xFF, 0xE0, 0x00])

if( len(sys.argv) != 2):
    print("\n Usage python3 %s <mp3File>" % sys.argv[0])
    exit()
# if

filepath = sys.argv[1]

basename = os.path.basename(filepath)
fname = os.path.splitext(basename)[0]

filepath_pic = fname + "_pic.mp3"
filepath_jpg = fname + ".jpg"


shutil.copyfile(filepath, filepath_pic)
 
id3_tags = ID3(filepath_pic)
if not id3_tags:
    print('no tags')
    os.remove(filepath_pic)
    exit()
# if

# search picture tag
has_pic = False
for k, v in id3_tags.items():
    if 'APIC' in k:
        has_pic = True
        pic = v
# for

if not has_pic:
    print('no picture')
    os.remove(filepath_pic)
    exit()
# if

pic_data = pic.data
pic_mime = pic.mime
desc = pic.desc

print('mime: ', pic_mime)
print('type: ', pic.type)
print('encoding: ', pic.encoding)

print('desc: ', desc)
desc_bin = desc.encode('latin1')
print('desc bin: ', desc_bin)

# TODO:
# I don't know the original character encode
try:
    desc_decode = desc_bin.decode('cp932')
    print('desc decode: ', desc_decode)
except UnicodeDecodeError:
    print('UnicodeDecodeError')
# try

# search SOI
has_soi = False
for i in range(10):
    if (pic_data[i] == SOI[0] ) and (pic_data[i+1] == SOI[1] ):
        has_soi = True
# if

if has_soi:
    print('has SOI')
    os.remove(filepath_pic)
    exit()
# if

img_data = SOI + pic_data

with open(filepath_jpg, "wb") as fout:                  
    fout.write(img_data)
# with

print("saved: ", filepath_jpg)


# replace picture tag
id3_tags.delall('APIC')

id3_tags.add(
    APIC(
       encoding=3, # 3 is for utf-8
        mime='image/jpeg', # image/jpeg or image/png
        type=3, # 3 is for the cover image
        desc='Cover',
        data=img_data
    )
)

id3_tags.save(v2_version=3)

print("recovered: ", filepath_pic)

