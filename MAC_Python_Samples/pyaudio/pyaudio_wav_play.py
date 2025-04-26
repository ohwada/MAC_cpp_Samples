# Python: play sound file using  pyaudio 
# Only wav Not suport mp3
# 2025-04-10  K.OHWADA

# https://qiita.com/hisshi00/items/62c555095b8ff15f9dd2

import pyaudio
import wave
import sys

CHUNK = 1024
EMPTY = ''


def play_sound(fpath):
	wf = wave.open(fpath, "rb")
	p = pyaudio.PyAudio()
	stream = p.open(format=p.get_format_from_width(wf.getsampwidth()), channels=wf.getnchannels(), rate=wf.getframerate(), output=True)
	data = wf.readframes(CHUNK)

	while data != EMPTY:
		stream.write(data)
		data = wf.readframes(CHUNK)
# end

	stream.stop_stream()
	stream.close()
	p.terminate()
#end


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

