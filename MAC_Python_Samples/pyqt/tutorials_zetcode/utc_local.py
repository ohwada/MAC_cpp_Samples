# Pyton: The example determines the current universal and local date and time.
# 2025-04-10  K.OHWADA

# https://zetcode.com/gui/pyqt5/datetime/

from PyQt5.QtCore import QDateTime, Qt

now = QDateTime.currentDateTime()

print('Local datetime: ', now.toString(Qt.ISODate))
print('Universal datetime: ', now.toUTC().toString(Qt.ISODate))

# The offsetFromUtc gives the difference between universal time and local time in seconds.
seconds = now.offsetFromUtc()
hours = seconds/3600
print('The offset from UTC is: ',  hours, ' hours')
