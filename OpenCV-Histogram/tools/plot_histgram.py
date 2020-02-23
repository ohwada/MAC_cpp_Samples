#!/usr/bin/env python

# plot histgram from text file created by OpenCV
# 2020-01-01 K.OHWADA

import sys
import os
import matplotlib.pyplot as plt

LF = '\n'
COMMA = ','

# convIntArray
def convIntArray(line):
    arr = line.split(COMMA)
    vals = []
    for item in arr:
        s = item.strip()
        if (s == '') or (s == LF):
            continue
        vals.append( int(s) )
    return vals
#---

# plot_histogram_color
def plot_histogram_color(histRed, histGreen, histBlue, title_color, output):
    x = range( len(histRed) )
    f, axarr = plt.subplots(4, sharex=True)

# 0: mix
    axarr[0].set_title(title_color)
    axarr[0].bar(x, histRed, color='red', alpha=0.2)
    axarr[0].bar(x, histGreen, color='green', alpha=0.2)
    axarr[0].bar(x, histBlue, color='blue', alpha=0.2)

# 1: Red
    axarr[1].bar(x, histRed, color='red', alpha=1.0)

# 2: Green
    axarr[2].bar(x, histGreen, color='green', alpha=1.0)

# 3: Blue
    axarr[3].bar(x, histBlue, color='blue', alpha=1.0)

    plt.savefig(output)
    plt.show()
#-----

# plot_histogram_gray
def plot_histogram_gray(histGray, output, title_gray):
    x = range( len(histGray) )
    plt.title(title_gray)
    plt.bar(x, histGray, color='gray')
    plt.savefig(output)
    plt.show()
#---

args = sys.argv

if (len(args) <2 ):
    print("Usage: " +  args[0] +  " <histgramFileName> ")
    exit()

input_file = args[1]
basename = os.path.basename(input_file)
name, ext = os.path.splitext(basename)
output = name + "_plot.png"
base = name.rstrip('_hist')
title_color = "ocv RGB Histgram: " + base
title_gray = "ocv Gray Histgram: " + base

f = open(input_file)
lines = f.readlines()
f.close()

len_lines = len(lines)
if len_lines == 1:
    histGray = convIntArray(lines[0])
    plot_histogram_gray(histGray, output, title_gray)
    exit()
elif len_lines != 3:
    print('invalid data')
    exit()
#---

histRed = convIntArray(lines[0])
histGreen = convIntArray(lines[1])
histBlue = convIntArray(lines[2])

plot_histogram_color(histRed, histGreen, histBlue, title_color, output)

