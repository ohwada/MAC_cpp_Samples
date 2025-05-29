# we receive data from QInputDialog dialog
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/dialogs/
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import (QWidget, QPushButton, QLineEdit,
                             QInputDialog, QApplication)
import sys


# Window
WIN_TITLE="PyQt5 Input Dialog"
PX=50
PY=50
WIDTH= 300
HEIGHT= 200

# button
BTN_TEXT = "Dialog"

# Dialog
DLG_TITLE = "Input Dialog"                                     
DLG_LABEL = "Enter your name:"


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        self.btn = QPushButton(BTN_TEXT, self)
        self.btn.move(20, 20)
        self.btn.clicked.connect(self.showDialog)
        self.le = QLineEdit(self)
        self.le.move(130, 22)
# end

    def showDialog(self):
        text, ok = QInputDialog.getText(self, DLG_TITLE, DLG_LABEL)
        print('text: ', text)
        if ok:
            self.le.setText(str(text))
# end

def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
    main()
# end