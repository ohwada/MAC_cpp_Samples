# class GaussianKernel
# calculate Gaussian Kernel
# 2020-01-01 K.OHWADA

from math import exp

# class GaussianKernel
class GaussianKernel(): 

# gaussian
    def gaussian(self, x, mu, sigma):
        return exp( -(((x-mu)/(sigma))**2)/2.0 )
# ---

# createKernel2d
    def createKernel2d(self, radius, sigma):
        kernel_size = 2*radius+1

# compute the actual kernel elements
        hkernel = [self.gaussian(x, radius, sigma) for x in range(kernel_size)]
        vkernel = [x for x in hkernel]
        kernel2d = [[xh*xv for xh in hkernel] for xv in vkernel]

# normalize the kernel elements
        kernelsum = sum([sum(row) for row in kernel2d])
        kernel2d = [[x/kernelsum for x in row] for row in kernel2d]
        return  kernel2d
# ---

# printTitle
    def printTitle(self, radius, sigma):
        ksize = 2*radius+1
        str_size = str(ksize)
        str_sigma = str(sigma)
        print("Gaussian Kernel: " + str_size +  " x " + str_size + " sigma= " + str_sigma)
 # ---

# printKernel
    def printKernel(self, kernel2d, format):
        for line in kernel2d:
            for x in line:
                print (format % x),
            print
 # ---
