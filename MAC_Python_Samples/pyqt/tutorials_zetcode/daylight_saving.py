# Pyton: The example checks if the datetime is in the daylight saving time.
# 2025-04-10  K.OHWADA

# https://zetcode.com/gui/pyqt5/datetime/


from PyQt5.QtCore import QDateTime, QTimeZone, Qt


now = QDateTime.currentDateTime()

print(f'Time zone: {now.timeZoneAbbreviation()}')

if now.isDaylightTime():
    print(f'The current date falls into DST time')
else:
    print(f'The current date does not fall into DST time')

