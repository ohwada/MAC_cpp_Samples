# Python: template of Font Picker usinng pyQt5
# 2025-04-10  K.OHWADA

# PyQT Font widget
#  https://pythonprogramming.net/font-picker-widget-pyqt-tutorial/

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

 
WIN_TITLE = "PyQt5 Font Picker"
PX = 10
PY = 10
WIDTH = 500
HEIGHT = 300

QUIT = "Quit"

DOWNLOAD = "Download"

EXTRACTION = "Extraction"

FONT = "Font"

CTRL_Q = "Ctrl+Q"

MENU_FILE = "&File"

MENU_EXTRACT = "&GET TO THE CHOPPAH!!!"

FPATH_WIN_ICON = "icons/python_logo.png"

FPATH_FLEE_ICON = "icons/car.png"


class Window(QMainWindow):

    def __init__(self):
        super(Window, self).__init__()
        self.setGeometry(PX, PY, WIDTH , HEIGHT)
        self.setWindowTitle(WIN_TITLE)
        self.setWindowIcon(QIcon(FPATH_WIN_ICON))
        extractAction = QAction(MENU_EXTRACT, self)
        extractAction.setShortcut(CTRL_Q)
        extractAction.setStatusTip('Leave The App')
        extractAction.triggered.connect(self.close_application)
        self.statusBar()
        mainMenu = self.menuBar()
        fileMenu = mainMenu.addMenu(MENU_FILE)
        fileMenu.addAction(extractAction)
        self.home()
# end

    def home(self):
        btn = QPushButton(QUIT, self)
        btn.clicked.connect(self.close_application)
        btn.resize(btn.minimumSizeHint())
        btn.move(0,100)

        extractAction = QAction(QIcon(FPATH_FLEE_ICON), 'Flee the Scene', self)
        extractAction.triggered.connect(self.close_application)
        self.toolBar = self.addToolBar(EXTRACTION)
        self.toolBar.addAction(extractAction)

        fontChoice = QAction(FONT, self)
        fontChoice.triggered.connect(self.font_choice)
        self.toolBar = self.addToolBar(FONT)
        self.toolBar.addAction(fontChoice)

        checkBox = QCheckBox('Shrink Window', self)
        checkBox.move(100, 25)
        checkBox.stateChanged.connect(self.enlarge_window)

        self.progress = QProgressBar(self)
        self.progress.setGeometry(200, 80, 250, 20)

        self.btn = QPushButton(DOWNLOAD,self)
        self.btn.move(200,120)
        self.btn.clicked.connect(self.download)

        obj_name =  self.style().objectName()
        print(  obj_name)
        self.styleChoice = QLabel( obj_name, self)

        comboBox = QComboBox(self)
        comboBox.addItem("motif")
        comboBox.addItem("Windows")
        comboBox.addItem("cde")
        comboBox.addItem("Plastique")
        comboBox.addItem("Cleanlooks")
        comboBox.addItem("windowsvista")

        comboBox.move(50, 250)
        self.styleChoice.move(50,150)
        comboBox.activated[str].connect(self.style_choice)

        self.show()
# end

    def font_choice(self):
        font, valid = QFontDialog.getFont()
        print('font: ', font)
        print('vald: ', valid)
        if valid:
            self.styleChoice.setFont(font)
# end

    def style_choice(self, text):
        self.styleChoice.setText(text)
        QApplication.setStyle(QStyleFactory.create(text))
# end

    def download(self):
        self.completed = 0
        while self.completed < 100:
            self.completed += 0.0001
            self.progress.setValue( int(self.completed) )
# end
        
    def enlarge_window(self, state):
        if state == Qt.Checked:
            self.setGeometry(50,50, 1000, 600)
        else:
            self.setGeometry(50, 50, 500, 300)
        # end

    def close_application(self):
        choice = QMessageBox.question(self, 'Extract!',
                                            "Get into the chopper?",
                                            QMessageBox.Yes | QMessageBox.No)
        if choice == QMessageBox.Yes:
            print("Good bye!")
            sys.exit()
        else:
            pass
# end        
         
def run():
    app = QApplication(sys.argv)
    win = Window()
    sys.exit(app.exec_())
# end

# main
run()

