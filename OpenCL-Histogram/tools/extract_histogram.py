#!/usr/bin/env python
# -*- coding: utf-8 -*-

# extract and plot histgram from image file
# 2020-01-01 K.OHWADA


# original : https://github.com/wblakecannon/DataCamp/blob/master/15-introduction-to-data-visualization-with-python/04-analyzing-time-series-and-images/10-extracting-histograms-from-a-color-image.py


import sys
import os
import matplotlib.pyplot as plt


# plot_hist
def plot_hist(image, plot_title, output):

# Extract 2-D arrays of the RGB channels: red, blue, green
    red, green, blue = image[:,:,0], image[:,:,1], image[:,:,2]

# Flatten the 2-D arrays of the RGB channels into 1-D
    red_pixels = red.flatten()
    blue_pixels = blue.flatten()
    green_pixels = green.flatten()

# Overlay histograms of the pixels of each color in the bottom subplot
    f, axarr = plt.subplots(4, sharex=True)
    plt.xlim((0,256))
# 0: mix
    axarr[0].set_title(plot_title)
    axarr[0].hist(red_pixels, bins=256, normed=True, color='red', alpha=0.2)
    axarr[0].hist(blue_pixels, bins=256, normed=True, color='blue', alpha=0.2)
    axarr[0].hist(green_pixels, bins=256, normed=True, color='green', alpha=0.2)

# 1: Red
    axarr[1].hist(red_pixels, bins=256, normed=True, color='red', alpha=1.0)

# 2: Green
    axarr[2].hist(green_pixels, bins=256, normed=True, color='green', alpha=1.0)

# 3: Blue
    axarr[3].hist(blue_pixels, bins=256, normed=True, color='blue', alpha=1.0)

# Display the plot
    plt.savefig(output)
    plt.show()
#----

args = sys.argv

if (len(args) <2 ):
    print("Usage: " +  args[0] +  " <histgramFileName> ")
    exit()

input_file = args[1]
basename = os.path.basename(input_file)
name, ext = os.path.splitext(basename)
output = name + "_hist.png"
plot_title = "RGB Histgram: " + name

image = plt.imread(input_file)
plot_hist(image, plot_title, output)
