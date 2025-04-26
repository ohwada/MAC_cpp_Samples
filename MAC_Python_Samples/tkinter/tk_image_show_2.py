# Python: show image file with Tk window
# suport png Not suport jpeg
# Not resize image
# adjust Window size to fit Image size
# 2025-04-10  K.OHWADA

# https://qiita.com/nnahito/items/2ab3ad0f3adacc3314e6

import tkinter as tk
import sys
import os

# Canvas
PX=0
PY=0

# image
IX=0
IY=0

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

# image
img = tk.PhotoImage(file =fpath)
iw = img.width()
ih = img.height()

# adjust Window size to fit Image size
win_size = FORMAT % (iw , ih)
win.geometry(win_size)

# adjust Canvas size to fit Image size
canvas = tk.Canvas(win, width =iw, height =ih)

canvas.place(x=PX, y=PY)

px=iw/2
py=ih/2
canvas.create_image(px, py, image = img)

win.mainloop()



