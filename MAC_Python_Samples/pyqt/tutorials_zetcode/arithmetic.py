# Pyton: The example determines the current datetime 
# and add or subtract days, seconds, months, and years.
# 2025-04-10  K.OHWADA


# https://zetcode.com/gui/pyqt5/datetime/


from PyQt5.QtCore import QDateTime, Qt


now = QDateTime.currentDateTime()

print(f'Today:', now.toString(Qt.ISODate))
print(f'Adding 12 days: {now.addDays(12).toString(Qt.ISODate)}')
print(f'Subtracting 22 days: {now.addDays(-22).toString(Qt.ISODate)}')

print(f'Adding 50 seconds: {now.addSecs(50).toString(Qt.ISODate)}')
print(f'Adding 3 months: {now.addMonths(3).toString(Qt.ISODate)}')
print(f'Adding 12 years: {now.addYears(12).toString(Qt.ISODate)}')
