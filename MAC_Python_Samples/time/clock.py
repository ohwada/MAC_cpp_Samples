# Python: display the current time at 1 second intervals
# 2025-04-10  K.OHWADA

import time
import sys

SLEEP = 1 # 1 sec
MAX = 100

CLOCK_FORMAT = '%H:%M:%S'

 # print_overwrite
 # erase the line and print message
PRINT_FORMAT= '\033[2K\033[G%s'


def   print_overwrite(msg):
	sys.stdout.write(PRINT_FORMAT % msg)
	sys.stdout.flush()
# end


def  print_overwrite_now():
	now = time.strftime(CLOCK_FORMAT)
	print_overwrite(now)
# end


# nain
# print loop
for i in range(MAX):
	print_overwrite_now()
	time.sleep(SLEEP)
# end	



