# Python: show image file with Tk window
# suport png Not suport jpeg
# show image in original size. 
# If image size is larger than the window, 
# adjust The window size to fit the image size
# Image size is limited to  the screen size
# If image size is larger than the screen , 
# show only a portion of image
# 2025-04-10  K.OHWADA

# https://qiita.com/nnahito/items/2ab3ad0f3adacc3314e6

import tkinter as tk
import sys
import os

# Window
PX= 50
PY= 50

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

# image
img = tk.PhotoImage(file =fpath)
iw = img.width()
ih = img.height()

# adjust Window size to fit Image size
win_geometry = FORMAT % (iw , ih, PX, PY)
win.geometry(win_geometry)

# adjust Canvas size to fit Image size
canvas = tk.Canvas(win, width =iw, height =ih)

canvas.place(x=CX, y=CY)

px=iw/2
py=ih/2
canvas.create_image(px, py, image = img)

win.mainloop()



