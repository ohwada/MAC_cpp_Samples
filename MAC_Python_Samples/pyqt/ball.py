# Python: tunction for animate Bouncing  Ball
# 2025-04-10  K.OHWADA


from PyQt5.QtCore import QRect

FPATH_IMG = "soccer_ball.png"

BALL_SIZE = 32

def getRect(width, height, w_min_ratio, w_max_ratio, h_min_ratio, h_max_ratio):
    left = int(w_min_ratio * width)
    right = int(w_max_ratio * width)
    top = int(h_min_ratio * height)
    bottom= int(h_max_ratio * height)
    w = right - left
    h = bottom - top
    rect = QRect(left, top, w, h)
    return rect
# end


