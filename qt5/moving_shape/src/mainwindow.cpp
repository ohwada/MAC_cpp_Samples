// BadproG.com
#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "MovingShape.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _shape = new MovingShape(this);
    setCentralWidget(_shape);
    setWindowTitle("BadproG.com");
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow() {
    delete _shape;
    delete ui;
}


