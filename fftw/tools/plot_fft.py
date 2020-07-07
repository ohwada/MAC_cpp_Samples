#!/usr/bin/env python
# plot FFT spectrum in line grspth
# 2020-03-01 K.OHWADA

import matplotlib.pyplot as plt
import sys
import os

args = sys.argv

if (len(args) <2 ):
    print("Usage: " +  args[0] +  " <histgramFileName> ")
    exit()
#---

filepath = args[1]

fname = os.path.splitext(os.path.basename(filepath))[0]
fft_title = "FFT: " + fname
output = "plot_" + fname + ".png"

f = open(filepath)
lines = f.readlines()
f.close()

freq_list = []
amp_list = []
max_amp = 0
at_freq = 0
list_index = 0
for line in lines:
    num, freq, amp = line.strip().split(',')
    freq_float = float(freq)
    amp_float = float(amp)
    if amp_float > max_amp:
        max_amp = amp_float
        at_freq = freq_float
        list_index = int(num)
    #---
    freq_list.append( freq_float)
    amp_list.append(amp_float)
#---

print("max_amp", max_amp)
print("at_freq", at_freq)
print("list_index", list_index)

x_list = []
y_list = []
for i in range(0, 2*list_index):
    x_list.append(freq_list[i])
    y_list.append(amp_list[i])
#--

x = at_freq + 20
y = max_amp - 20
text = "%d \n at %.1f Hz" % ( int(max_amp), at_freq)
fig = plt.figure(figsize =(6, 6))
ax = fig.add_subplot(111)
ax.text(x, y, text, size = 15)
plt.title(fft_title)
plt.plot(x_list, y_list,  marker="o")
plt.show()
fig.savefig(output)
