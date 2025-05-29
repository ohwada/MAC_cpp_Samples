# This program creates a context menu.
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/menustoolbars/
# modify: 2025-04-10  K.OHWADA


import sys
from PyQt5.QtWidgets import QMainWindow, qApp, QMenu, QApplication


# Window
WIN_TITLE ="PyQt5 Context Menu"
PX=50
PY=50
WIDTH= 300
HEIGHT= 200

# Menu
NEW = "New"
OPEN = "Open"
QUIT = "Quit"


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
# end
    def initUI(self):
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
# end

    def contextMenuEvent(self, event):
        # called When you left-click the mouse
        print('contextMenuEvent')
        cmenu = QMenu(self)
        newAct = cmenu.addAction(NEW)
        openAct = cmenu.addAction(OPEN)
        quitAct = cmenu.addAction(QUIT)

# The get the coordinates of the mouse pointer from the event object. 
# The mapToGlobal method translates the widget coordinates to the global screen coordinates.
        action = cmenu.exec_(self.mapToGlobal(event.pos()))

        if action == quitAct:
            print('quitAct')
            qApp.quit()
        elif action == newAct:
            print('newAct')
        elif action ==  openAct:
            print(' openAct')
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
