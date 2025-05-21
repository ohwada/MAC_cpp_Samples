# Example to show connecting events that occur when the figure closes.
# 2025-04-10  K.OHWADA

# https://matplotlib.org/stable/gallery/event_handling/close_event.html


import matplotlib.pyplot as plt


def on_close(event):
    print('Closed Figure!')
# end

fig = plt.figure()
fig.canvas.mpl_connect('close_event', on_close)

plt.text(0.35, 0.5, 'Close Me!', dict(size=30))
plt.show()

