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

# Canvas
PX=0
PY=0
WIDTH = 300
HEIGHT = 300

# window
FORMAT = "%dx%d"


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

win_size = FORMAT % (WIDTH , HEIGHT)
win.geometry(win_size)

# Canvas
canvas = tk.Canvas(win, width=WIDTH,  height =HEIGHT)
canvas.place(x=PX, y=PY)

# image
img = tk.PhotoImage(file =fpath)
iw = img.width()
ih = img.height()

px=iw/2
py=ih/2
canvas.create_image(px, py, image = img)

win.mainloop()



