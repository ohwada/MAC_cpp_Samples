#!/usr/bin/env python
#coding: utf-8

# show album picture in mp3 file
# 2020-03-01 K.OHWADA# reference : https://www.programcreek.com/python/example/73822/mutagen.id3.APIC


from mutagen.id3 import ID3
from PIL import Image
import io 
import sys
import os


# main
if( len(sys.argv) != 2):
    print("\n Usage python3 %s <mp3File>" % sys.argv[0])
    exit()
# if

filename = sys.argv[1]

basename = os.path.basename(filename)
fname = os.path.splitext(basename)[0]
fname_out = fname + "_pic.jpg"

tags = ID3(filename)
flag = False;
for k, v in tags.items():
    if 'APIC' in k:
        print('found APIC');
        flag = True;
        pic = v
# for

if not flag:
    print("NOT get picture")
    exit()
# if

pic_data = pic.data
mime = pic.mime
pic_type = pic.type
pic_encoding = pic.encoding
desc = pic.desc
print('mime: ', mime)
print('type: ', pic_type)
print('encoding: ', pic_encoding)
print('desc: ', desc)

# search SOI
has_soi = False
for i in range(10):
    if (pic_data[i] == 0xFF ) and (pic_data[i+1] == 0xD8 ):
        has_soi = True
# if

if not has_soi:
    print('NOT has SOI')
    exit()
# if

with open(fname_out, "wb") as fout:                  
    fout.write(pic_data)
# with

print("saved: ", fname_out)

img_io = io.BytesIO(pic_data)
img = Image.open(img_io)
img.show()

