#!/usr/bin/env python
#coding: utf-8

# convrt text encode for sample_enc.h
# 2020-03-01 K.OHWADA
# reference : https://docs.python.org/ja/3/library/codecs.html#module-codecs

import sys

# 
def print_byte_list(byte_list):
    for i in  range(len(byte_list)):
        byte = byte_list[i]
        print('(char) %X , ' % byte, end='' )
    #---
#---

# print_char_list
def print_char_list(char_list, enc):
    list_len = len(char_list)
    for i in range(list_len):
        if(i == 0):
            print( ' { ', end='')
        #-----
        c = char_list[i]
        c_byte_list = c.encode(enc, 'ignore')
        print_byte_list( c_byte_list)
        if (i == list_len - 1):
            print( ' }; ', end='')
        #-----
        print(' // ', c)
    #-----
#-----

# main
text = 'あいうえお'

if (len(sys.argv) != 2):
    print("\n Usage python3 %s <text>" % sys.argv[0])
else:
    text = sys.argv[1]
#-----


print()
print(text)
char_list = [text[i] for i in range(len(text))]

print("\n const char SJIS[] = ")
print_char_list(char_list, 'shift_jis')

print("\n const char EUCJP[] = ")
print_char_list(char_list, 'eucjp')

print("\n const char UTF8[] = ")
print_char_list(char_list, 'utf8')

print("\n const char UTF16[] = ")
print_char_list(char_list, 'utf_16')

print("\n const char UTF16BE[] = ")
print_char_list(char_list, 'utf_16_be')

print("\n const char UTF16LE[] = ")
print_char_list(char_list, 'utf_16_le')

print("\n const char UTF32BE[] = ")
print_char_list(char_list, 'utf_32_be')
