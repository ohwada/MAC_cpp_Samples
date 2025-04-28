# Python: get the full path of user directory on Mac
# 2025-04-10  K.OHWADA

# https://docs.python.org/ja/3.13/library/os.path.html

import os

MAC_USR_DOC_DIR = "~/Documents"

# main
dir = os.path.expanduser(MAC_USR_DOC_DIR)
print(dir)
