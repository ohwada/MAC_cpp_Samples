# Python: show animation  using matplotlib FuncAnimation
# save anime gif
# 2025-04-10  K.OHWADA


# https://qiita.com/yubais/items/c95ba9ff1b23dd33fde2

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

FIG_TITLE = "Func Amination"

MAX_IMS =10

NUM = 100

INTERVAL=100  #100ms

FRAMES=10

WRITER="pillow"

OUTFILE = "mat_anime_func.gif"


def plot(data):
# create random graph
    plt.cla()                     
    rand = np.random.randn(NUM)   
    im = plt.plot(rand)
    return im        
# end

# main
fig = plt.figure(num=FIG_TITLE)
ani = animation.FuncAnimation(fig, plot, interval=INTERVAL, frames=FRAMES)
ani.save(OUTFILE, writer=WRITER)
plt.show()
