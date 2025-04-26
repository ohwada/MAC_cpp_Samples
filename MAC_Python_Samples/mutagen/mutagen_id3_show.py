# Python: show ID3 tags
# 2025-04-10  K.OHWADA

# https://note.nkmk.me/python-mutagen-mp3-id3/

from mutagen.easyid3 import EasyID3
import sys

def show_id3_tags(fpath):
    tags = EasyID3(fpath)
    print(tags.pprint())
# end


# main
args = sys.argv
argc = len(args)
script = args[0]

if argc < 2:
	print("Usage: python %s  <mp3 filepath>" % script)
	exit()
# end

fpath = args[1]
show_id3_tags(fpath)



