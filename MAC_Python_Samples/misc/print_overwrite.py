# Python: print overwrite
# 2025-04-10  K.OHWADA

import time
import sys

 #  print_overwrite
# erase the line and print message
PRINT_FORMAT= '\033[2K\033[G%s'


def  print_overwrite(msg):
	sys.stdout.write(PRINT_FORMAT % msg)
	sys.stdout.flush()
# end


# main
for i in range(100):
	msg= str(i)
	print_overwrite(msg)
	time.sleep(1)
# end