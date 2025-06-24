# Python: Pos class for animate Bouncing  Ball
# 2025-04-10  K.OHWADA


# Window
WIDTH = 480
HEIGHT = 360

# Ball
FPATH_IMG = "soccer_ball.png"

BALL_SIZE = 32

# Pos
MIN_X = int(0.2 * WIDTH)
LEFT_X = int(0.9 * WIDTH)
MAX_X = LEFT_X - BALL_SIZE

MIN_Y = int(0.1 * HEIGHT)
BOTTOM_Y= int(0.9 * HEIGHT)
MAX_Y = BOTTOM_Y - BALL_SIZE

INIT_X = MIN_X
INIT_Y = MIN_Y 
V_X = 4 # velocity x
V_Y = 6 # velocity y

BALL_E = 0.75 # the coefficient of repulsion
BALL_DT = 0.5 # Distance travelled by the ball

# Rect
RECT_LEFT = MIN_X
RECT_TOP = MIN_Y
RECT_WIDTH = LEFT_X - MIN_X
RECT_HEIGHT =  BOTTOM_Y - MIN_Y


# calc Ball position
# https://qiita.com/MENDY/items/e1b432df1e0bfe8b680c
class Pos():
    def __init__(self):
        self.x = INIT_X
        self.y = INIT_Y
        self.v_x = V_X
        self.v_y = V_Y
# end

    def update_pos(self):
        self.x += self.v_x * BALL_DT
        self.y += self.v_y * BALL_DT
    #x limit
        if self.x > MAX_X:
            self.x = MAX_X
            self.update_velocity_x()
        elif self.x < MIN_X:
            self.x = MIN_X
            self.update_velocity_x()
# end
# y limit
        if self.y > MAX_Y:
            self.y = MAX_Y
            self.update_velocity_y()
        elif self.y < MIN_Y:
            self.y = MIN_Y
            self.update_velocity_y()
# end
        return self.x, self.y
# end

    def update_velocity_x(self):
        self.v_x = - BALL_E * self.v_x
    # end

    def update_velocity_y(self):
        self.v_y = - BALL_E * self.v_y
# end




