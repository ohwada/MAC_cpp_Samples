# Python: play sound file using simpleaudio 
# Only wav Not suport mp3
# 2025-04-10  K.OHWADA

# https://qiita.com/hisshi00/items/62c555095b8ff15f9dd2

import simpleaudio
import sys


def play_sound(fpath):
	wav_obj = simpleaudio.WaveObject.from_wave_file(fpath)
	play_obj = wav_obj.play()
	play_obj.wait_done()
# end


# main
args = sys.argv
argc = len(args)
script = args[0]

if argc < 2:
	print("Usage: python %s  <wav filepath>" % script)
	exit()
# end

fpath = args[1]
play_sound(fpath)

