# Python: Analog Clock using tkinter
# 2025-04-10  K.OHWADA

# https://mulberrytassel.com/python-practice-tkinter-11/

import tkinter as tk
import math
import datetime
import time
import threading

# window
WIN_TITLE = "Analog Clock"

PX = 50
PY = 50
WIDTH    = 400      
HEIGHT   = 400      

FORMAT = "%dx%d+%d+%d"

# Canvas
CX   = int(WIDTH/2)
CY   = int(HEIGHT/2) 
CENTER = (CX, CY)

# Circle
CIRCLE_X0 = 10
CIRCLE_Y0 = 10
CIRCLE_WIDTH = 360
CIRCLE_HEIGHT = 360

CIRCLE_FILL = "white"
CIRCLE_OUTLINE = "darkgray"

# hour mark
 # (text, degree)
DIC_HOUR＿MARK = {"1":300,"2":330,"3":0,"4":30,"5":60,"6":90,"7":120,"8":150,"9":180,"10":210,"11":240,"12":270}

HOUR＿MARK_LENGTH     = 160 

FONT_SIZE = 24

# Clock 
# time for the hand to rotate one lap
# ONE_LAP_HOUR = 12 # 12 houurs
# ONE_LAP_MIN = 60 # 60 minutess = one hour
# ONE_LAP_SEC = 60 # 60 secinds = one minute

# angle per unit time
SEC_DEG = 6 # 360/NE_LAP_SEC
MIN_DEG = 6 # 360/ONE_LAP_MIN
HOUR_DEG = 30 # 360/# ONE_LAP_HOUR

# unit conversion
ONE_HOUR_MIN = 60 # one hour = 60minutes
ONE_MIN_SEC = 60 # one minute = 60 srconds

# Clock Hands
HOUR_HAND_LENGTH = 120      
MINUTE_HAND_LENGTH = 160      
SECOND_HAND_LENGTH = 150  
    
     

HOUR_WIDTH = 8
MINUTE_WIDTH = 5
SECOND_WIDTH = 2

DEG_BASE = 90  # Angle at 12 oclock     
 
TAG_HAND    = "hand" 



UPDATE_INTERVAL  = 0.2  # 200 msec


def update_time():
 
    while True:
        now = datetime.datetime.now()

        hour = now.hour  + float(float(now.minute)/ONE_HOUR_MIN) 
        deg_h = int(DEG_BASE - HOUR_DEG * hour )    
        deg_m = int(DEG_BASE - MIN_DEG * now.minute)                        
        deg_s = int( DEG_BASE - SEC_DEG * now.second)                        
 
        rad_h = math.radians(deg_h)
        rad_m = math.radians(deg_m)
        rad_s = math.radians(deg_s)

# Position of the tip of hand
        px_h = round(math.cos(rad_h)*HOUR_HAND_LENGTH)   
        py_h = round(math.sin(rad_h)*HOUR_HAND_LENGTH)    
        px_m = round(math.cos(rad_m)*MINUTE_HAND_LENGTH)    
        py_m = round(math.sin(rad_m)*MINUTE_HAND_LENGTH)    
        px_s = round(math.cos(rad_s)*SECOND_HAND_LENGTH)    
        py_s = round(math.sin( rad_s)*SECOND_HAND_LENGTH)    
 
# draw hands
        canvas.create_line(CENTER, (CX+px_h), (CY-py_h), width=HOUR_WIDTH, tags=TAG_HAND)
        canvas.create_line(CENTER, (CX+px_m), (CY-py_m), width=MINUTE_WIDTH, tags=TAG_HAND)
        canvas.create_line(CENTER, (CX+px_s), (CY-py_s), width=SECOND_WIDTH, tags=TAG_HAND)
 
        time.sleep(UPDATE_INTERVAL )
 
# clear hands 
        canvas.delete(TAG_HAND)
 # end

# Window
win = tk.Tk()

win.title(WIN_TITLE)

win_geometry = FORMAT % (WIDTH , HEIGHT, PX, PY)
win.geometry(win_geometry)

canvas = tk.Canvas(win, width=WIDTH, height=HEIGHT)

 # circle
canvas.create_oval(CIRCLE_X0, CIRCLE_Y0, CIRCLE_WIDTH, CIRCLE_HEIGHT, outline=CIRCLE_OUTLINE, fill=CIRCLE_FILL)
 
## hour mark
for mark, deg in DIC_HOUR＿MARK.items():
    rad = math.radians(deg)
    x = round(math.cos(rad) * HOUR_MARK_LENGTH)
    y = round(math.sin(rad) * HOUR＿MARK_LENGTH)
    canvas.create_text((CX+x), (CY+y), text=mark, font=(None, FONT_SIZE))
# end
 
canvas.pack()
 
thread = threading.Thread(target=update_time, daemon=True)
thread.start()
 
canvas.mainloop()
