# This program shows a confirmation message box 
# when we click on the close button of the application window.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/firstprograms/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import QWidget, QMessageBox, QApplication


# Window
WIN_TITLE="PyQt5 Simple"
PX=50
PY=50
WIDTH= 250
HEIGHT= 150


class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()
# end

    def initUI(self):

        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle('Message box')
        self.show()
# end

    def closeEvent(self, event):

        reply = QMessageBox.question(self, 'Message',
                                     "Are you sure to quit?", QMessageBox.Yes |
                                     QMessageBox.No, QMessageBox.No)

        if reply == QMessageBox.Yes:

            event.accept()
        else:

            event.ignore()
# end

def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
    main()
# end