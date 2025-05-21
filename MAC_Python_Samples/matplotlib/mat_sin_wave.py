# Python: plot Sin Wave using matplotlib
# 2025-04-10  K.OHWADA

# https://qiita.com/soiSource/items/a33d101213b2ec2f8ba6

import matplotlib.pyplot as plt
import numpy as np


WIN_TITLE = "Matplotlib Sin Wave"

PLT_TITLE = "Sin Wave"

OUTFILE = "mat_sin_wave.png"

NUM = 500

# main
fig = plt.figure(WIN_TITLE)

plt.title(PLT_TITLE)

x = np.linspace(0,  2*np.pi, NUM)

plt.plot(x, np.sin(x))

plt.savefig(OUTFILE)

plt.show()
