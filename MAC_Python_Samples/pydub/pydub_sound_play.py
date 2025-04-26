# Python: play sound using pydub 
# suport mp3
# 2025-04-10  K.OHWADA

# https://qiita.com/hisshi00/items/62c555095b8ff15f9dd2

from pydub import AudioSegment

from pydub.playback import play

import sys
import os


def play_sound(fpath):
	ext = os.path.splitext(fpath)[1][1:]
	sound = AudioSegment.from_file(fpath, format=ext)
	play(sound)
# end


# main
args = sys.argv
argc = len(args)
script = args[0]

if argc < 2:
	print("Usage: python %s  <sound filepath>" % script)
	exit()
# end

fpath = args[1]
play_sound(fpath)

