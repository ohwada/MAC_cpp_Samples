# Python: Dejital Clock with Tk
# 2025-04-10  K.OHWADA

# https://office54.net/python/tkinter/after-method-schedule

import tkinter as tk
import time

#Window
TITLE='Digital Clock'
WIN_SIZE='300x100'

# Label
FONT_FAMILY='times'
FONT_SIZE=50
FONT_STYLE='bold'

# Color
GRAY ='gray'

# after 1sec
DELAY =1000


def update_clock():
	global id_after
	now = time.strftime('%H:%M:%S')
	label_clock.configure(text=now)
	id_after = label_clock.after(DELAY, update_clock)
# end


def stop_time():
	label_clock.after_cancel( id_after)
# end


# Window
win = tk.Tk()
win.title(TITLE)
win.geometry(WIN_SIZE)
win.config(bg=GRAY)

# Label
label_clock = tk.Label(win, font=(FONT_FAMILY, FONT_SIZE, FONT_STYLE) )
label_clock.pack()

# Button
button_stop = tk.Button(win, text='Stop', command=stop_time)
button_stop.pack()

update_clock()

win.mainloop()

