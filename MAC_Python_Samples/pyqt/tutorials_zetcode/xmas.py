# Pyton: The example calculates the number of days passed from the last XMas 
# and the number of days until the next XMas.
# 2025-04-10  K.OHWADA

# https://zetcode.com/gui/pyqt5/datetime/

from PyQt5.QtCore import QDate

now = QDate.currentDate()

year = now.year()

print('this year: ', year)

xmas1 = QDate( (year-1), 12, 24) # last year

xmas2 = QDate(year, 12, 24) # this year

dayspassed = xmas1.daysTo(now)
print(f'{dayspassed} days have passed since last XMas')

nofdays = now.daysTo(xmas2)
print(f'There are {nofdays} days until next XMas')


