// BadproG.com
#ifndef MOVING_SHAPE_1_MAINWINDOW_H
#define MOVING_SHAPE_1_MAINWINDOW_H

#include <QMainWindow>

class MovingShape;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MovingShape *_shape;

protected:
};

#endif // MOVING_SHAPE_1_MAINWINDOW_H
