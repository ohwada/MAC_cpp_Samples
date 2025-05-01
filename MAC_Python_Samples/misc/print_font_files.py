# Python: print installed font files in font_installed_dirs
# 2025-04-10  K.OHWADA

# https://programwiz.org/2021/05/08/python-draw-images-for-font-list/#google_vignette

from PIL import ImageFont, ImageDraw
import os
import sys


PLATFORM_LIST_LINUX = ("linux", "linux2")
PLATFORM_WIN = "WIN32"
PLATFORM_MAC = "darwin"

ENV_KEY_WIN = "WINDIR"
ENV_KEY_LINUX = "XDG_DATA_DIRS"

DIR_USR_SHAR = "/usr/share"
FONTS = "fonts"
 
MAC_SYSTEM_FONT_DIR = "/System/Library/Fonts"
MAC_LIB_FONT_DIR = "/Library/Fonts"
MAC_USR_FONT_DIR = "~/Library/Fonts"

TTF = "ttf"
TTC = "ttc"

def get_platform_num():
    if sys.platform in PLATFORM_LIST_LINUX:
        return 1
    elif sys.platform == PLATFORM_WIN:
        return 2
    elif sys.platform == PLATFORM_MAC:
        return  3
    raise Exception(f"unsupported platform:{sys.platform}")
# end

def get_linux_font_dirs():
    dirs = os.environ.get(ENV_KEY_LINUX)
    if not dirs:
        dirs = DIR_USR_SHAR
    return [os.path.join(d, ONTS) for d in dirs.split(":")]
# end

def get_win_font_dirs():
    d = os.environ.get(ENV_KEY_WIN)
    return [os.path.join(d, FONTS)]
# end

def get_mac_font_dirs():
    return [   MAC_SYSTEM_FONT_DIR,
    MAC_LIB_FONT_DIR, 
    os.path.expanduser(MAC_USR_FONT_DIR)]
# end

def get_font_installed_dirs():
    num = get_platform_num()
    if num == 1:
        return get_linux_font_dirs()
    elif num == 2:
        return get_win_font_dirs()
    if num == 3:
        return  get_mac_font_dirs()
# end


def get_family_name(fpath):
    try:
        font = ImageFont.truetype(fpath)
        familyName, fontName = font.getname()
        return familyName
    except OSError:
        print('OSError')
        return 'invalid'
# end


# main
dirs = get_font_installed_dirs()
print(dirs)
for d in dirs:
    print(d)
    files = os.listdir(d)
    num = len(files)
    print(num, " files")
    for f in files:
        fpath = os.path.join(d, f)
        ext= os.path.splitext(os.path.basename(fpath) )[1][1:]
        if  os.path.isfile(fpath) and ( (ext == TTF) or (ext == TTC) ):
            familyName = get_family_name(fpath)
            print(f, ': ',  familyName)
# end


