# Python: show image file with Label in Tk window
# 2025-04-10  K.OHWADA

# https://kuroro.blog/python/Z7k1LSyDyiDHtD5UCjmG/

import tkinter as tk
import sys
import os

# Window
PX= 50
PY= 50
WIDTH = 400
HEIGHT = 400

FORMAT = "%dx%d+%d+%d"

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

# image
img = tk.PhotoImage(file =fpath)

label = tk.Label(width=WIDTH, height= HEIGHT, image=img)

label.pack()

win.mainloop()



