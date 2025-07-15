# Bouncing  Ball Animation using matplotlib FuncAnimation
# 2025-04-10  K.OHWADA


import matplotlib.pyplot as plt
import matplotlib.animation as ani
import matplotlib.patches as patches
import math
from PIL import Image
from pos import Pos  
from ball import *
import numpy as np
import glob
import sys, os


FIG_TITLE = "Bousing Ball"

WIDTH = 480
HEIGHT = 360

DPI = 100.0

FIGSIZE = ( float(WIDTH/ DPI), float(HEIGHT / DPI) )

OFF = "off"

# Anim
UPDATE_INTERVAL = 500 # msec

FRAMES = 120 # 60 sec

BLUE =  "#0000ff"

# ball rect
rect =  getRect(WIDTH, HEIGHT, 0.2, 0.9, 0.1, 0.9)

r_left = rect.left()

r_right = rect.right()

r_top = rect.top()

r_bottom = rect.bottom() 

R_X =   r_left

R_Y = r_top

R_WIDTH= r_right - r_left

R_HEIGHT =  r_bottom - r_top

# Pos
X_MIN = r_left

X_MAX = r_right - BALL_SIZE

Y_MIN = r_top

Y_MAX = r_bottom  - BALL_SIZE

X_INIT = X_MIN

Y_INIT = Y_MIN

VX= Pos.VX

VY = - Pos.VY

# anime gif
GIF_OUTFILE = "mat_anime_ball_img.gif"
GIF_WRITER= "pillow"


def update_anim(i):
	plt.cla()
	plt.axis(OFF) 
	ax = plt.axes()
	ax.set_xlim(0, WIDTH)
	ax.set_ylim(HEIGHT, 0)
	rect = patches.Rectangle((R_X, R_Y), R_WIDTH, R_HEIGHT, ec=BLUE, fill=False)
	ax.add_patch(rect)

	x, y =  pos.update_pos()
	left =float(x)
	right = float(left+ BALL_SIZE)
	top = float(y)
	bottom = float(top+ BALL_SIZE)
	extent = (left, right, bottom, top)
	plt.imshow(img_ball, extent=extent)
# end


## Main
fig = plt.figure(num= FIG_TITLE, figsize=FIGSIZE)
img = Image.open(FPATH_IMG)
img_ball = np.array(img)
pos = Pos()
pos.set_range(X_MIN, X_MAX, Y_MIN, Y_MAX)
pos.set_init(X_INIT, Y_INIT, VX, VY)

anime = ani.FuncAnimation(fig, update_anim, interval=UPDATE_INTERVAL, frames=FRAMES)
anime.save(GIF_OUTFILE, writer= GIF_WRITER)
plt.show()  

