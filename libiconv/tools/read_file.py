#!/usr/bin/env python

# read encoded text file
# 2020-03-01 K.OHWADA
# reference : https://docs.python.org/ja/3/library/codecs.html#module-codecs

import os
import sys

if (len(sys.argv) != 2):
    print("\n Usage python3 %s <textFile>" % sys.argv[0])
    exit()
else:
    filename = sys.argv[1]
#-----

basename = os.path.basename(filename)
fname = os.path.splitext(basename)[0]
file_enc = fname.split('_')[1]

if(file_enc == 'sjis'):
    enc = 'sjis'
elif(file_enc == 'eucjp'):
    enc = 'eucjp'
elif(file_enc == 'utf16'):
    enc = 'utf_16'
elif(file_enc == 'utf16be'):
    enc = 'utf_16_be'
elif(file_enc == 'utf16le'):
    enc = 'utf_16_le'
elif(file_enc == 'utf32'):
    enc = 'utf_32'
elif(file_enc == 'utf32be'):
    enc = 'utf_32_be'
elif(file_enc == 'utf32le'):
    enc = 'utf_32_le'
else:
    print('NOT find encode')
    exit()
#-----

print('encode: ', enc)

reader = open(filename, encoding=enc)

lines = reader.readlines()

print()
for line in lines:
    print(line)
#-----

