# Python: play sound file using sounddevice
# Only wav Not suport mp3
# 2025-04-10  K.OHWADA

# https://qiita.com/hisshi00/items/62c555095b8ff15f9dd2

import sounddevice as sd
import wave
import numpy as np
import sys

LIST = 'list'
INT16 ='int16'


def play_sound(fpath):
	wf = wave.open(fpath)
	fs = wf.getframerate()
	data = wf.readframes(wf.getnframes())
	data = np.frombuffer(data, dtype= INT16)
	sd.play(data, fs)
	status = sd.wait()


def print_device_list():
	device_list = sd.query_devices()
	print(device_list)
	for device_number in sd.default.device:
		print(device_number)
		print(device_list[device_number])
# end


#main
args = sys.argv
argc = len(args)
script = args[0]

if argc < 2:
	print("Usage: python %s  <wav filepath>" % script)
	exit()
# end

fpath = args[1]
if fpath == LIST:
	print_device_list()
	exit()
# end 

play_sound(fpath)



