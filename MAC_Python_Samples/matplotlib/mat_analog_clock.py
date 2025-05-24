# Python: Analog Clock using matplotlib 
# 2025-04-10  K.OHWADA

# https://gist.github.com/jul/39d178f10ee79d080f0f

import matplotlib.pyplot as plt
from time import time, localtime

# Constant are CAPitalized in python by convention
from cmath import  pi as PI, e as E

# Window
WIN_TITLE = "Analog Clock"

# hide axis
AXIS = 'off'

# ticks
MAX_TICKS = 60

TICK_WIDTH = 1
TICK5_WIDTH = 5

# one letter color
# https://matplotlib.org/2.0.1/api/colors_api.html#module-matplotlib.colors
TICK_COLOR =  'k-' # black
TICK5_COLOR =  'k-' # black

PLT_INTERVAL = 0.1 # 0.1 sec

# fixing the weired / behaviour in python 2 by forcing cast in float
# 2 * PI = one full turn in radians (SI) second makes a
# 60th of a turn per seconds
# an arc is a fraction of turn
RAD_PER_SEC = 2.0 * PI /60.0

# 60 times slower
RAD_PER_MIN = RAD_PER_SEC / 60

# wall clock are not on 24 based because human tends to
# know if noon is passed
RAD_PER_HOUR = RAD_PER_MIN / 12

# hand length
SEC_HAND_LENGTH = 0.9
MIN_HAND_LENGTH = 0.8
HOUR_HAND_LENGTH = 0.6

MIN_HAND_WIDTH = 3
HOUR_HAND_LWIDTH = 4

# one letter color
SEC_HAND_COLOR  = 'r-' # red
MIN_HAND_COLOR  = 'b-' # blue
HOUR_HAND_COLOR  = 'g-'  # grren


def on_close(event):
    print('on_close')
    # plt.ioff()
    exit()
# end

# main
fig = plt.figure(WIN_TITLE)
fig.canvas.mpl_connect('close_event', on_close)

plt.axis(AXIS)

# correcting python notations j => I  
I = complex("j")

# I == rectangular coordonate (0,1) in complex notation
origin_vector_hand = I

# maplotlib does not plot lines using the classical
# (x0,y0), (x1,y1) convention
# but prefers (x0,x1) (y0,y1)
to_xx_yy = lambda c1,c2 : [(c1.real, c2.real), (c1.imag, c2.imag)] 

# black magic
# plt.ion() # Enable interactive mode
# plt.show()

# Euler's Formula is used to compute the rotation
# using units in names to check unit consistency
# rotation is clockwise (hence the minus)
# Euler formular requires a measure of angle (rad)
rot_sec = lambda sec : E ** (-I * sec * RAD_PER_SEC )
rot_min = lambda min : E ** (-I *  min * RAD_PER_MIN )
rot_hour = lambda hour : E ** (-I * hour * RAD_PER_HOUR )

# drawing the ticks and making them different every
# division of 5
for n in range(MAX_TICKS ):
    plt.plot(
        *to_xx_yy(
            origin_vector_hand * rot_sec(n),
            .95 * I * rot_sec(n)
        )+[n% 5 and TICK_COLOR or TICK5_COLOR],
        lw= n% 5 and TICK_WIDTH or TICK5_WIDTH
    )

    plt.draw()
# end

# computing the offset between the EPOCH and the local political convention of time
# [3]: hour [4]: minute [5]: second
diff_offset_in_sec = (time() % (24*3600)) - localtime()[3]*3600 -localtime()[4] * 60.0 - localtime()[5]   

while True:
    t = time() # unix time
    # sexagesimal base conversion
    s= t%60
    m = m_in_sec = t%(60 * 60)
    h = h_in_sec = (t- diff_offset_in_sec)%(24*60*60)
    # applying a rotation AND and homothetia for the vectors expressent as (complex1, ccomplex2)
    # using the * operator of complex algebrae to do the job
    l = plt.plot( *to_xx_yy(
            -.1 * origin_vector_hand * rot_sec(s),
             SEC_HAND_LENGTH * origin_vector_hand * rot_sec(s)) + [SEC_HAND_COLOR]  )
    j = plt.plot( *to_xx_yy(0, MIN_HAND_LENGTH * origin_vector_hand * rot_min( m )) + [MIN_HAND_COLOR] , lw= MIN_HAND_WIDTH)
    k = plt.plot( *to_xx_yy(0, HOUR_HAND_LENGTH * origin_vector_hand * rot_hour(h)) +[ HOUR_HAND_COLOR] , lw= HOUR_HAND_LWIDTH)
    plt.pause(PLT_INTERVAL)
    ## black magic : remove elements on the canvas.
    l.pop().remove()
    j.pop().remove()
    k.pop().remove()
# while end

