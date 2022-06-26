#include "CMainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(PDA_Maze);
    QApplication m_app(argc, argv);

    CMainWindow m_MainWindow;
    m_MainWindow.show();

    return m_app.exec();
}
