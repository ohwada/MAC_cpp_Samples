# Python: read sqlite db
# show data in Dialog
# 2025-04-10  K.OHWADA

#  https://www.tutorialspoint.com/pyqt5/pyqt5_database_handling.htm


import sys
from PyQt5.QtSql import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

# Window
WIN_TITLE="PyQt5 Database Demo"
PX=50
PY=50
WIDTH = 400
HEIGHT = 300

# Button
BTN0 = "Add a row"
BTN1 = "del a row"

# Database
DB_TYPE = 'QSQLITE'
DB_NAME = 'sportsdatabase.db'
TBL_NAME = 'sportsmen'


def initializeModel(model):
    model.setTable(TBL_NAME)
    model.setEditStrategy(QSqlTableModel.OnFieldChange)
    model.select()
    model.setHeaderData(0, Qt.Horizontal, "ID")
    model.setHeaderData(1, Qt.Horizontal, "First name")
    model.setHeaderData(2, Qt.Horizontal, "Last name")
# end

def createView(title, model):
   view = QTableView()
   view.setModel(model)
   view.setWindowTitle(title)
   return view
# end

def addrow():
    global model
    print(model.rowCount())
    ret = model.insertRows(model.rowCount(), 1)
    print (ret)
# end

def findrow(i):
   delrow = i.row()
# end

def window():
    global model
    db = QSqlDatabase.addDatabase(DB_TYPE)
    db.setDatabaseName(DB_NAME)
    model = QSqlTableModel()
    delrow = -1
    initializeModel(model)
    view1 = createView("Table Model (View 1)", model)
    view1.clicked.connect(findrow)

    dlg = QDialog()
    dlg.setWindowTitle(WIN_TITLE)
    print(  dlg.rect() )
    dlg.setGeometry(PX, PY, WIDTH,HEIGHT)
    layout = QVBoxLayout()
    layout.addWidget(view1)
    btn0 = QPushButton(BTN0)
    btn0.clicked.connect(addrow)
    layout.addWidget(btn0)
    btn1 = QPushButton(BTN1)
    btn1.clicked.connect(lambda: model.removeRow(view1.currentIndex().row()))
    layout.addWidget(btn1)
    dlg.setLayout(layout)
    return dlg
# end


if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = window()
    win.show()
    sys.exit(app.exec_())
# end
