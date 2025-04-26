# Python: display Tk window
# 2025-04-10  K.OHWADA

# https://qiita.com/nnahito/items/ad1428a30738b3d93762

import tkinter as tk

#Window
WIN_TITLE='Tk'
WIN_SIZE='100x50'

# Label
LABEL_TEXT = 'Hello'


# Window
win = tk.Tk()

win.title(WIN_TITLE)

win.geometry(WIN_SIZE)

# Label
label = tk.Label(win, text=LABEL_TEXT)

label.pack()

win.mainloop()





