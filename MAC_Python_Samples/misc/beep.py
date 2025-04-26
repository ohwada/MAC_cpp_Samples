# Python: beep
# 2025-04-10  K.OHWADA

import time
import sys

# beep
BEL = '\007'

BEEP_SLEEP = 0.1 # 0.1 sec
BEEP_MAX = 10

def beep():
	for i in range(BEEP_MAX):
		sys.stdout.write(BEL)
		sys.stdout.flush()
		time.sleep(BEEP_SLEEP)
# end

# main
beep()
