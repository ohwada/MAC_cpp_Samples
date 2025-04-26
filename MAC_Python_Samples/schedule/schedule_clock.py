# Python: display the current time at 1 second intervals 
# The alarm will sound after 10 seconds
# Stop afer 20 seconds
# 2025-04-10  K.OHWADA


import schedule
import time
import datetime
import sys


# beep
BEL = '\007'
BEEP_SLEEP = 0.1 # 0.1 sec
BEEP_MAX = 100

CLOCK_FORMAT = '%H:%M:%S'
TARGET_FORMAT = '%H:%M:%S'


 # print_overwrite
 # erase the line and print message
PRINT_FORMAT= '\033[2K\033[G%s'


def beep():
	for i in range(BEEP_MAX):
		sys.stdout.write(BEL)
		sys.stdout.flush()
		time.sleep(BEEP_SLEEP)
# end


def   print_overwrite(msg):
	sys.stdout.write(PRINT_FORMAT % msg)
	sys.stdout.flush()
# end


def update_clock():
	now = time.strftime(CLOCK_FORMAT)
	print_overwrite(now)
# end


def alarm():
	beep()
# end


def stop():
	print()
	print("stop")
	exit()
# end


# main
dt_now = datetime.datetime.now()

# The alarm will sound after 10 seconds
dt_alarm = dt_now + datetime.timedelta(seconds = 10)
target_alarm = dt_alarm.strftime(TARGET_FORMAT)
schedule.every().day.at(target_alarm).do( alarm)
print('alarm: ',  target_alarm)

# Stop afer 20 seconds
dt_stop = dt_now + datetime.timedelta(seconds = 20)
target_stop = dt_stop.strftime(TARGET_FORMAT)
schedule.every().day.at(target_stop).do(stop)
print('stop: ',  target_stop)

# display the current time at 1 second intervals 
schedule.every(1).seconds.do(update_clock)

# run loop
while True:
	schedule.run_pending()
	time.sleep(1)
# end


