# Pyton: we compute the Gregorian date and the Julian day for today.
# 2025-04-10  K.OHWADA

# https://zetcode.com/gui/pyqt5/datetime/


from PyQt5.QtCore import QDate, Qt

now = QDate.currentDate()

print('Gregorian date for today:', now.toString(Qt.ISODate))
print('Julian day for today:', now.toJulianDay()) 

