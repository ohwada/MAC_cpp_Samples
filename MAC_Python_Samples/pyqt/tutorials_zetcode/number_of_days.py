# Pyton: The example prints the number of days in a month and year for the chosen date.
# 2025-04-10  K.OHWADA
# https://zetcode.com/gui/pyqt5/datetime/

from PyQt5.QtCore import QDate, Qt

now = QDate.currentDate()

d = QDate(1945, 5, 7)

print(f'Days in month: {d.daysInMonth()}')
print(f'Days in year: {d.daysInYear()}')
