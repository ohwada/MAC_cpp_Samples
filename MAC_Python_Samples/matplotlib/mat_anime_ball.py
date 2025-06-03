# Bouncing  Ball Animation using matplotlib FuncAnimation
# midify: 2025-04-10  K.OHWADA

# https://qiita.com/MENDY/items/e1b432df1e0bfe8b680c


import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as ani
import math


# Figure
FIG_TITLE = "Bouncing Ball"

# Graph
XLABEL = "X [m]"
YLABEL = "Y [m]"

ASPECT = "equal"

GRID = True

# Ball
INIT_X = 0
INIT_Y = 0
V_X =2 # velocity x
V_Y = 3 # velocity y
BALL_SIZE = 0.2
BALL_E = 0.75 # the coefficient of repulsion
BALL_DT = 0.05 # Distance travelled by the ball

BALL_LABEL= "Predicit"
BALL_COLOR = "r" # red

# The size of a person is 15cm radius
CIRCLE_SIZE = 0.2

# Text
TEXT_X = 0.05
TEXT_Y = 0.9
TEXT_INIT =  ''

TEXT_FORMAT = "step = {0}"

# This level of resolution is fine for drawing circles.
STEPS = 100
 
MAX_XY = 5
MIN_XY = -5

# Animation
INTERVAL=50
FRAMES=100

# anime gif
OUTFILE = "mat_anime_ball.gif"
WRITER= "pillow"


class Ball():
    def __init__(self, init_x, init_y, v_x, v_y, ball_size, e, dt):
        self.x = init_x
        self.y = init_y
        self.v_x = v_x
        self.v_y = v_y
        self.size = ball_size
        self.e = e # the coefficient of repulsion
        self.dt = dt
# end

    def state_update(self):
        self.x += self.v_x * self.dt 
        self.y += self.v_y * self.dt
    # prevents fgoing out of range
        if self.x > MAX_XY:
            self.x = MAX_XY
            self.velocity_x_update()
        elif self.x < MIN_XY:
            self.x = MIN_XY
            self.velocity_x_update()
# end
        if self.y > MAX_XY:
            self.y = MAX_XY
            self.velocity_y_update()
        elif self.y < MIN_XY:
            self.y = MIN_XY
            self.velocity_y_update()
# end
        return self.x, self.y
# end

    def velocity_x_update(self):
        self.v_x = -self.e * self.v_x
    # end

    def velocity_y_update(self):
        self.v_y = -self.e * self.v_y
# end


class Drawing():
    def __init__(self, ax):
        self.color = []
        self.ax = ax
        self.ball_img, = ax.plot([], [], color= BALL_COLOR)
# end
    def draw_circle(self, center_x, center_y, circle_size=CIRCLE_SIZE):
        # Initialization
        self.circle_x = [] 
        self.circle_y = [] 
        for i in range( STEPS):
            self.circle_x.append(center_x + circle_size*math.cos(i*2*math.pi/ STEPS))
            self.circle_y.append(center_y + circle_size*math.sin(i*2*math.pi/ STEPS))
        # end
        self.ball_img.set_data(self.circle_x, self.circle_y)
        return self.ball_img, 
# end

def update_anim(i):
    # This i will increase every time it is updated
    # plt.cla() 
    ball_x, ball_y =  ball.state_update()
    ball_img, = drawer.draw_circle(ball_x, ball_y)
    # Time
    step_text.set_text(TEXT_FORMAT.format(i))
    return ball_img, 
# end


## Main
fig = plt.figure(num= FIG_TITLE)
ax = fig.add_subplot(111)

# Axis maximum and minimum
ax.set_xlim(MIN_XY, MAX_XY)
ax.set_ylim(MIN_XY, MAX_XY)

# Axis aspect ratio 
# square, equal length per unit
ax.set_aspect(ASPECT)

# Axis label
ax.set_xlabel(XLABEL) 
ax.set_ylabel(YLABEL) 

# Grid
ax.grid(GRID)

# Legend
# ax.legend()

# Step number
step_text = ax.text(TEXT_X, TEXT_Y, TEXT_INIT, transform=ax.transAxes)

# Initial settings
ball_img, = plt.plot([], [], label= BALL_LABEL, color= BALL_COLOR)

# create ball
ball = Ball(INIT_X,  INIT_Y, V_X, V_Y, BALL_SIZE, BALL_E, BALL_DT)

drawer = Drawing(ax)

anime = ani.FuncAnimation(fig, update_anim, interval=INTERVAL, frames=FRAMES)

anime.save(OUTFILE, writer= WRITER)

plt.show()  

