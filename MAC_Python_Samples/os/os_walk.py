# Python: recursively walk a directory tree
# 2025-04-10  K.OHWADA

# https://www.sejuku.net/blog/63816

import os

# main
for curDir, dirs, files in os.walk("test"):
    print("===================")
    print("current directory: ", curDir)
    print("sub directories:", dirs)
    print("files: ", files)
# end

