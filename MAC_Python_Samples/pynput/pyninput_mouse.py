# Python:  detect mouse ivent
# 2025-04-10  K.OHWADA

# https://qiita.com/universato/items/11bfac1d522c1c1ec2a3

from pynput.mouse import Listener


def on_click(x, y, button, pressed):
    if pressed:
        print(' Pressed on {:5.1f}, {:5.1f}'.format(x, y))
# end

# main

with Listener(on_click = on_click) as listener:
	 listener.join()
# end






