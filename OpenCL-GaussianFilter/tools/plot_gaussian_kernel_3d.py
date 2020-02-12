#!/usr/bin/env python

# plot Gaussian Kernel 3d graph
# 2020-01-01 K.OHWADA

# reference : https://note.nkmk.me/python-matplotlib-mplot3d/

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from matplotlib import cm

LF = '\n'
UNDER_BAR = '_'

# getStrSize
def getStrSize(radius):
    ksize = 2 * radius + 1
    str_size = str(ksize)
    return str_size
#---

# getStrSigma
def getStrSigma(sigma):
    str_sigma = "%0.1f" % sigma
    return str_sigma
#---

# createOutputFile
def createOutputFile(radius, sigma):

    str_size = getStrSize(radius)
    str_sigma = getStrSigma(sigma)
    output = "gaussian_kernel_3d"  + UNDER_BAR + str_size + "x" + str_size + UNDER_BAR + str_sigma + UNDER_BAR + ".png"
    return output
#---

# createTitle
def createTitle(radius, sigma):
    str_size = getStrSize(radius)
    str_sigma = getStrSigma(sigma)
    title = "Gaussian Kernel" + LF + str_size + "x" + str_size + " sigma=" + str_sigma
    return title
#---

radius = 50
sigma = 10

output = createOutputFile(radius, sigma)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

x = y = np.arange(-radius, radius, 0.5)

X, Y = np.meshgrid(x, y)

zz =( X**2 + Y**2)/(2 * sigma**2)
Z = np.exp(-zz) / (2 * np.pi * sigma)

ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.coolwarm)

title = createTitle(radius, sigma)
plt.title(title)

plt.savefig(output)
print("save to: " + output)

plt.show()
