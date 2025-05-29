# Pyton: The example prints the current date, 
# date and time, and time in various formats.
# 2025-04-10  K.OHWADA

# https://zetcode.com/gui/pyqt5/datetime/

from PyQt5.QtCore import QDate, QTime, QDateTime, Qt

now = QDate.currentDate()

print(now.toString(Qt.ISODate))
print(now.toString(Qt.DefaultLocaleLongDate))

datetime = QDateTime.currentDateTime()

print(datetime.toString())

time = QTime.currentTime()

print(time.toString(Qt.DefaultLocaleLongDate))

