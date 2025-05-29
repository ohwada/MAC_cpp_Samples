# Python: We print the version of Qt library and PyQt5 module.
# 2025-04-10  K.OHWADA

# https://zetcode.com/gui/pyqt5/introduction/


from PyQt5.QtCore import QT_VERSION_STR
from PyQt5.Qt import PYQT_VERSION_STR

print('Qt Version : ', QT_VERSION_STR)
print('PyQt Version : ', PYQT_VERSION_STR)

