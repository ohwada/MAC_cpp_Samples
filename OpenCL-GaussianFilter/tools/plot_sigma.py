# plot xy graph
#　to compare Gaussian Kernel by sigma　
# 2020-01-01 K.OHWADA

import sys
from math import exp
import matplotlib.pyplot as plt
from gaussian_kernel_class import GaussianKernel 


# main   

radius = 5

gk = GaussianKernel()

kernel2d1 = gk.createKernel2d(radius, 1.5)
kernel2d2 = gk.createKernel2d(radius, 3.0)
kernel2d3 = gk.createKernel2d(radius, 6.0)

gk.printTitle(radius, 3.0)
gk.printKernel(kernel2d2, "%.3f")

start = -radius
end = radius+1
x = range(start, end, 1)
print(x)

y1 = kernel2d1[radius]
y2 = kernel2d2[radius]
y3 = kernel2d3[radius]

plt.plot(x, y1, label='sigma 1.5')
plt.plot(x, y2 , label='sigma 3.0')
plt.plot(x, y3 , label='sigma 6.0')

plt.title('GaussianKernel')
plt.legend()
plt.show()
