# Python: judge platform
# 2025-04-10  K.OHWADA

# https://programwiz.org/2021/05/08/python-draw-images-for-font-list/#google_vignette

import sys


PLATFORM_WIN = "WIN32"
PLATFORM_LIST_LINUX = ("linux", "linux2")
PLATFORM_MAC = "darwin"

def get_platform_num():
    if sys.platform in PLATFORM_LIST_LINUX:
        return 1
# end
    if sys.platform == PLATFORM_WIN:
        return 2
# end
    if sys.platform == PLATFORM_MAC:
        return  3
# end
    raise Exception(f"unsupported platform:{sys.platform}")
# end

# main
num = get_platform_num()
if num == 1:
    print('Linux')
elif num == 2:
    print('Windows')
elif num == 3:
    print('Mac')
# end
