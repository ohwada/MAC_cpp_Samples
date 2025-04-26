# Python: display the current time
# 2025-04-10  K.OHWADA

# https://docs.python.org/ja/3.13/library/datetime.html

import datetime

# Year-Mounth-Day Hour:Minutes:Second Tomezone
FORMAT = '%Y-%m-%d (%a) %H:%M:%S %Z'

# nain
dt_now = datetime.datetime.now()
print( 'type: ', type(dt_now) )
print(dt_now)
str_now = dt_now.strftime(FORMAT)
print('now: ', str_now)
unix_now = dt_now.timestamp()
print('Unix time: ', unix_now)
# 10 days and 2 hours later
dt_later = dt_now + datetime.timedelta(days = 10, hours = 2)
str_later = dt_later.strftime(FORMAT)
print('10 days and 2 hours later: ')
print(str_later)

