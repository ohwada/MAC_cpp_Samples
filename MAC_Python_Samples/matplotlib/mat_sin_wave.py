# Python: plot sin wave using matplotlib
# 2025-04-10  K.OHWADA

# https://qiita.com/soiSource/items/a33d101213b2ec2f8ba6

import matplotlib.pyplot as plt
import numpy as np


WIN_TITLE = "matplotlib"

PLT_TITLE = "Sin Wave")

NUM = 500

x = np.linspace(0,  2*np.pi, NUM)

fig=plt.figure(WIN_TITLE)

plt.title(PLT_TITLE)

plt.plot(x, np.sin(x))

plt.show()
