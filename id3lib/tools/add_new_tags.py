#!/usr/bin/env python
#coding: utf-8

# add ID3 tags to MP3 file that has no tags
# reference : https://stackoverflow.com/questions/18369188/python-add-id3-tags-to-mp3-file-that-has-no-tags

import mutagen
from mutagen.easyid3 import EasyID3
import sys
import os
import shutil

# main
if( len(sys.argv) != 2):
    print("\n Usage python3 %s <mp3File>" % sys.argv[0])
    exit()
# if

filepath = sys.argv[1]

basename = os.path.basename(filepath)
fname = os.path.splitext(basename)[0]
filepath_new = fname + '_new_tags.mp3';

try:
    meta = EasyID3(filepath)
    print('ID3 tag already exists')
    exit()
except mutagen.id3.ID3NoHeaderError:
    shutil.copyfile(filepath, filepath_new)
    meta = mutagen.File(filepath_new, easy=True)
# try

# add new tags
meta.add_tags()
meta['title'] = fname
meta['artist'] = 'Jhon Do'
print('new tags', meta)

meta.save(filepath_new, v1=2)

print('saved: ', filepath_new)

