# Python: show animation using matplotlib ArtistAnimation
# Python: save anime gif
# 2025-04-10  K.OHWADA


# https://qiita.com/yubais/items/c95ba9ff1b23dd33fde2


import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

FIG_TITLE = "Artist Amination"

MAX_IMS =10

NUM = 100

INTERVAL=100  #100ms

WRITER="pillow"

OUTFILE = "mat_anime_artist.gif"


# main
fig = plt.figure(num=FIG_TITLE)
ims = []

for i in range(MAX_IMS):
# create ramdom graph
        rand = np.random.randn(NUM)     
        im = plt.plot(rand)            
        ims.append(im)                  
# end

ani = animation.ArtistAnimation(fig, ims, interval= INTERVAL)
ani.save(OUTFILE, writer= WRITER)
plt.show()



