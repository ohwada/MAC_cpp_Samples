# Python:  detect keyboard ivent
# 2025-04-10  K.OHWADA

# https://note.com/knz888/n/ned6b8da2229a

from pynput import keyboard


def on_key_press(key):
	try:
		print(f'Key pressed: {key.char}')
	except AttributeError:
		print(f'Special key pressed: {key}')
	if key == keyboard.Key.esc:
		print("ESC presed")
		exit()
# end


# main

with keyboard.Listener(on_press=on_key_press) as key_listener:
    key_listener.join()
# end
