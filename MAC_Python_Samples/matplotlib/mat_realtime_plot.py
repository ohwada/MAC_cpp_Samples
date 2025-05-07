# Python: realtime plot using matplotlib 
# continue plotting sin wave infinitely
# when you press the close button, the window disappears but the program Not finish
# 2025-04-10  K.OHWADA

# https://qiita.com/hausen6/items/b1b54f7325745ae43e47


import numpy as np
import matplotlib.pyplot as plt

WIN_TITLE = "Continuous Sin Wave"

X_DELTA  = 0.1

PLT_PAUSE =  0.01 # 10msec


def pause_plot():
    fig = plt.figure(WIN_TITLE)
    ax = fig.subplots()
    x = np.arange(-np.pi, np.pi, X_DELTA)
    y = np.sin(x)

# Must be plotted once for initialization
   # lines, = ax.plot(x, y)
    lines, = plt.plot(x, y)

    # endlss loop
    while True:
        x += X_DELTA
        y = np.sin(x)
        lines.set_data(x, y)

# when using set_data(), it seems that the axes are not set automatically.
# the sin wave will quickly disappear from the drawing range.
# therefore, the x-axis range needs to be adjusted appropriately.
        ax.set_xlim((x.min(), x.max()))

        plt.pause(PLT_PAUSE)
# while end
    plt.show()
# def end

if __name__ == "__main__":
    pause_plot()
