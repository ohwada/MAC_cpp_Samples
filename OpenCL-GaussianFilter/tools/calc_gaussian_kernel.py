#!/usr/bin/env python

# calculate Gaussian Kernel
# with gaussian_kernel_class
# 2020-01-01 K.OHWADA

import sys
from gaussian_kernel_class import GaussianKernel 

# main   
args = sys.argv

if (len(args) <2 ):
    print("Usage: ",  args[0], " <kernel radius> <sigma>")
    exit()
 # ---

radius = int(args[1])
sigma = float(args[2])

gk = GaussianKernel()
kernel2d = gk.createKernel2d(radius, sigma)
gk.printTitle(radius, sigma)
gk.printKernel(kernel2d, "%.3f")
