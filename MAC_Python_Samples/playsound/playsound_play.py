# Python: play sound file using playsound 
# suport mp3
# 2025-04-10  K.OHWADA

# https://qiita.com/hisshi00/items/62c555095b8ff15f9dd2

from playsound import playsound

import sys


# main
args = sys.argv
argc = len(args)
script = args[0]

if argc < 2:
	print("Usage: python %s  <soubd filepath>" % script)
	exit()
# end

fpath = args[1]
playsound(fpath)


