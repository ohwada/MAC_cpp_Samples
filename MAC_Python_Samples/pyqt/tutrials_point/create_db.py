# Python: create sqlite db
# 2025-04-10  K.OHWADA

#  https://www.tutorialspoint.com/pyqt5/pyqt5_database_handling.htm

import sys
from PyQt5.QtSql import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

# Database
DB_TYPE = 'QSQLITE'
DB_NAME = 'sportsdatabase.db'


def createDB():
    db = QSqlDatabase.addDatabase(DB_TYPE)
    db.setDatabaseName(DB_NAME)

    if not db.open():
        msg = QMessageBox()
        msg.setIcon(QMessageBox.Critical)
        msg.setText("Error in Database Creation")
        retval = msg.exec_()
        return False
# end

    query = QSqlQuery()
    query.exec_("create table sportsmen(id int primary key, ""firstname varchar(20), lastname varchar(20))")
    query.exec_("insert into sportsmen values(101, 'Roger', 'Federer')")
    query.exec_("insert into sportsmen values(102, 'Christiano', 'Ronaldo')")
    query.exec_("insert into sportsmen values(103, 'Ussain', 'Bolt')")
    query.exec_("insert into sportsmen values(104, 'Sachin', 'Tendulkar')")
    query.exec_("insert into sportsmen values(105, 'Saina', 'Nehwal')")
    print('create db')
    return True
# end

if __name__ == '__main__':
   app = QApplication(sys.argv)
   createDB()
# end