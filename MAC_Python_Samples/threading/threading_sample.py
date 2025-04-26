# Python: run two threads
# 2025-04-10  K.OHWADA

# https://dtnavi.tcdigital.jp/cat_system/language_061/


import threading
import time

def print_numbers():
# Thread that outputs numbers
	for i in range(10):
		print(i)
# end

def print_letters(letter):
# Thread that outputs characters
	for _ in range(10):
		print(letter)
# end

# main
thread1 = threading.Thread(target=print_numbers)
thread2 = threading.Thread(target=print_letters, args=('A', ))

thread1.start()
thread2.start()

