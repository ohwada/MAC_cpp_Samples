# we create a bit more complicated window layout using the QGridLayout manager.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/layout/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import (QWidget, QLabel, QLineEdit,
                             QTextEdit, QGridLayout, QApplication)



# Window
WIN_TITLE="PyQt5 Review"
PX= 50
PY= 50
WIDTH= 350
HEIGHT= 300

# GridLayout
SPACING = 10

# Label
TITLE = "Title"
AUTHOR = "Author"
REVIEW = "Review"


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
        title = QLabel(TITLE)
        author = QLabel(AUTHOR )
        review = QLabel(REVIEW)
        titleEdit = QLineEdit()
        authorEdit = QLineEdit()
        reviewEdit = QTextEdit()
        grid = QGridLayout()
        grid.setSpacing(SPACING)
        grid.addWidget(title, 1, 0)
        grid.addWidget(titleEdit, 1, 1)
        grid.addWidget(author, 2, 0)
        grid.addWidget(authorEdit, 2, 1)
        grid.addWidget(review, 3, 0)
        grid.addWidget(reviewEdit, 3, 1, 5, 1)
        self.setLayout(grid)
# end


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec_())
# end

if __name__ == '__main__':
    main()
# ebd
