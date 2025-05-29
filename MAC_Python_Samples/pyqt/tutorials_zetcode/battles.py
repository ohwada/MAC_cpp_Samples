# Pyton: The example counts the number of days passed since two historical events.
# 2025-04-10  K.OHWADA

# https://zetcode.com/gui/pyqt5/datetime/


from PyQt5.QtCore import QDate, Qt

# https://en.wikipedia.org/wiki/Battle_of_Borodino
borodino_battle = QDate(1812, 9, 7)

# https://en.wikipedia.org/wiki/Battle_of_Austerlitz
slavkov_battle = QDate(1805, 12, 2)

now = QDate.currentDate()

j_today = now.toJulianDay()
j_borodino = borodino_battle.toJulianDay()
j_slavkov = slavkov_battle.toJulianDay()

d1 = j_today - j_slavkov
d2 = j_today - j_borodino

print(f'Days since Slavkov battle: {d1}')
print(f'Days since Borodino battle: {d2}')
