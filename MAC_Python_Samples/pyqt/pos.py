# Python: Pos class for animate Bouncing  Ball
# 2025-04-10  K.OHWADA


# calc Ball position
# https://qiita.com/MENDY/items/e1b432df1e0bfe8b680c
class Pos():
    E = 0.75 # the coefficient of repulsion
    DT = 1.0 # Distance travelled by the ball
    VX = 6.0 # velocity x
    VY = 8.0 # velocity y

    def __init__(self):
        self.e = Pos.E
        self.dt = Pos.DT
        self.x_min = 0
        self.y_min = 0
        self.y_max = 0
        self.x = 0
        self.y = 0
        self.vx = Pos.VX
        self.vy = Pos.VY
# end

    def set_ball_param(self, e, dt):
        self.e = e
        self.dt = dt
# end

    def set_range(self, x_min, x_max, y_min, y_max):
        self.x_min = x_min
        self.x_max = x_max
        self.y_min = y_min
        self.y_max = y_max
# end

    def set_init(self, x_init, y_init, vx_init, vy_init):
        self.x = x_init
        self.y = y_init
        self.vx = vx_init
        self.vy = vy_init
# end

    def update_pos(self):
        self.x += self.vx * self.dt
        self.y += self.vy * self.dt
    #x limit
        if self.x >   self.x_max:
            self.x =    self.x_max
            self.update_velocity_x()
        elif self.x <   self.x_min:
            self.x =   self.x_min
            self.update_velocity_x()
# end
# y limit
        if self.y >   self.y_max:
            self.y =   self.y_max
            self.update_velocity_y()
        elif self.y <    self.y_min:
            self.y =    self.y_min
            self.update_velocity_y()
# end
        return self.x, self.y
# end

    def update_velocity_x(self):
        self.vx = -  self.e * self.vx
    # end

    def update_velocity_y(self):
        self.vy = -  self.e * self.vy
# end




