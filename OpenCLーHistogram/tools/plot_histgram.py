#!/usr/bin/env python

# plot histgram from text file created by OpenCL
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

# plot_histogram
def plot_histogram(histRed, histGreen, histBlue, title_hist, output):
    x = range( len(histRed) )
    f, axarr = plt.subplots(4, sharex=True)

# 0: mix
    axarr[0].set_title(title_hist)
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

args = sys.argv

if (len(args) <2 ):
    print("Usage: " +  args[0] +  " <histgramFileName> ")
    exit()

input_file = args[1]
basename = os.path.basename(input_file)
name, ext = os.path.splitext(basename)
output = name + "_plot.png"
base = name.rstrip('_hist')
title_hist = "ocl RGB Histgram: " + base

f = open(input_file)
lines = f.readlines()
f.close()

histRed = convIntArray(lines[0])
histGreen = convIntArray(lines[1])
histBlue = convIntArray(lines[2])

plot_histogram(histRed, histGreen, histBlue, title_hist, output)

