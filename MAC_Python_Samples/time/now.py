# Python: display the current time
# 2025-04-10  K.OHWADA

# https://docs.python.org/ja/3.13/library/time.html

import time

# Year-Mounth-Day Hour:Minutes:Second Tomezone
FORMAT = '%Y-%m-%d (%a) %H:%M:%S %Z'

# nain
local_now = time.localtime()
print( 'type: ', type(local_now) )
print(local_now)
str_now = time.strftime(FORMAT)
print('now: ',str_now)
unix_now = time.time()
print('Unix time: ', unix_now)



