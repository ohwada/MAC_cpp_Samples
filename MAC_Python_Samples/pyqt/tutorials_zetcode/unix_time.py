# Pyton: The example prints the Unix time 
# and converts it back to the QDateTime.
# 2025-04-10  K.OHWADA

# https://zetcode.com/gui/pyqt5/datetime/


from PyQt5.QtCore import QDateTime, Qt

now = QDateTime.currentDateTime()

unix_time = now.toSecsSinceEpoch() 
print(unix_time)

d = QDateTime.fromSecsSinceEpoch(unix_time)
print(d.toString(Qt.ISODate))
