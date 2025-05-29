# heckBox widget is used to toggle the title of window.
# Author: Jan Bodnar
#  https://zetcode.com/pyqt6/widgets/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import QWidget, QCheckBox, QApplication
from PyQt5.QtCore import Qt
import sys


# Window
WIN_TITLE="PyQt5 QCheckBox"
WIN_TITLE_BLANK = ' '
PX=50
PY=50
WIDTH= 350
HEIGHT= 250

# CheckBox
SHOW_TITLE = "Show title"


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# nd

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        cb = QCheckBox(SHOW_TITLE, self)
        cb.move(20, 20)
        cb.toggle()
        cb.stateChanged.connect(self.changeTitle)
# end

    def changeTitle(self, state):
        print('state: ', state)
        # if state == Qt.CheckState.Checked.value:
        if state == Qt.CheckState.Checked:
            self.setWindowTitle(WIN_TITLE)
        else:
            self.setWindowTitle(WIN_TITLE_BLANK)
# ebd


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec())
#end

if __name__ == '__main__':
    main()
#end
