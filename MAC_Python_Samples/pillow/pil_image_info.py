# Python: show Image info using Pillow
# 2025-04-10  K.OHWADA

# https://note.com/abay_ksg/n/n8c35220e16d0

from PIL import Image
from PIL.ExifTags import TAGS,GPSTAGS
import sys


def load_exif(path):
    ifd_dict = {}
    with Image.open(path) as im:
        exif = im.getexif()
    ifd_dict["Zeroth"] =  {TAGS[tag_id]: value for tag_id, value in exif.items() }
    ifd_dict["Exif"] =    {TAGS[tag_id]: value for tag_id, value in exif.get_ifd(0x8769).items()}
    ifd_dict["GPSInfo"] = {GPSTAGS[tag_id]: value for tag_id, value in exif.get_ifd(0x8825).items()}
    return ifd_dict,exif


def print_info(fpath):
    ifd_dict = load_exif(fpath)
    print("Exif info:")
    for ifd in ifd_dict:
	    print(ifd)
# end
    print()
    print("Image info: ")
    im = Image.open(fpath)
    for item in im.info.items():
	    print(item)
# end


# main
args = sys.argv
argc = len(args)
script = args[0]

if argc < 2:
	print("Usage: python %s  <image filepath>" % script)
	exit()
# end

fpath = args[1]
print_info(fpath)
