#  This example shows a QCalendarWidget widget.
# Author: Jan Bodnar
#  https://zetcode.com/pyqt6/widgets/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import (QWidget, QCalendarWidget,
        QLabel, QApplication, QVBoxLayout)
from PyQt5.QtCore import QDate
import sys


# Window
WIN_TITLE="PyQt5  Calendar"
PX=50
PY=50
WIDTH= 350
HEIGHT= 300


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        vbox = QVBoxLayout(self)
        cal = QCalendarWidget(self)
        cal.setGridVisible(True)
        cal.clicked[QDate].connect(self.showDate)
        vbox.addWidget(cal)
        self.lbl = QLabel(self)
        date = cal.selectedDate()
        self.lbl.setText(date.toString())
        vbox.addWidget(self.lbl)
        self.setLayout(vbox)
# en

    def showDate(self, date):
        print('date: ',date.toString() )
        self.lbl.setText(date.toString())
# end

def main():
    app = QApplication(sys.argv)
    win =  Window()
    win.show()
    sys.exit(app.exec())
# end

if __name__ == '__main__':
    main()
# end

