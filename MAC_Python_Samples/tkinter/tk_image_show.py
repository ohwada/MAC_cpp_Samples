# Python: show image file with Tk window
# suport png Not suport jpeg
# show image in original size
# If Image saize is smaller than the window,
# show image in original size  within the window
# If image size is larger than the window, 
# show only a portion of image
# 2025-04-10  K.OHWADA

# https://qiita.com/nnahito/items/2ab3ad0f3adacc3314e6

import tkinter as tk
import sys
import os

# Window
PX= 50
PY= 50
WIDTH = 400
HEIGHT = 400

FORMAT = "%dx%d+%d+%d"

# Canvas
CX=0
CY=0


# main
args = sys.argv
argc = len(args)
script = args[0]

if argc < 2:
	print("Usage: python %s  <image filepath>" % script)
	exit()
# end

fpath = args[1]

# Window
win = tk.Tk()

fname = os.path.basename(fpath)
win.title(fname)

win_geometry = FORMAT % (WIDTH , HEIGHT, PX, PY)
win.geometry(win_geometry)

# Canvas
canvas = tk.Canvas(win, width=WIDTH,  height =HEIGHT)
canvas.place(x=CX, y=CY)

# image
img = tk.PhotoImage(file =fpath)

# draw in center
px= WIDTH/2
py= HEIGHT/2

canvas.create_image(px, py, image = img)

win.mainloop()



