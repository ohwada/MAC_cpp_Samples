# Python: draw figures using matplotlib 
# 2025-04-10  K.OHWADA

#  https://note.nkmk.me/python-matplotlib-patches-circle-rectangle/

import matplotlib.pyplot as plt
import matplotlib.patches as patches


WIN_TITLE = "Figures"

# Set equal scaling (i.e., make circles circular) 
AXIS  = "scaled"

# same scaling for x and y.
ASPECT = "equal"

OUTFILE = "mat_draw_figures.png"


# main
fig = plt.figure(WIN_TITLE)

ax = plt.axes()

# fc = face color, ec = edge color
c = patches.Circle(xy=(0, 0), radius=0.5, fc='g', ec='r')
e = patches.Ellipse(xy=(-0.25, 0), width=0.5, height=0.25, fc='b', ec='y')
r = patches.Rectangle(xy=(0, 0), width=0.25, height=0.5, ec='#000000', fill=False)
ax.add_patch(c)
ax.add_patch(e)
ax.add_patch(r)

plt.axis(AXIS)

ax.set_aspect(ASPECT)

ax.set_axis_off()

plt.savefig(OUTFILE)

plt.show()

 
