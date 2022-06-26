#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>

#include "boardmodel.h"
#include "fifteenpushbutton.h"

// представление игры
class BoardView : public QWidget
{
    Q_OBJECT
public:
    explicit BoardView(QWidget *parent = nullptr);
    ~BoardView();

    // установить новую расстановку
    // is_rnd - создать случайную расстановку или нет
    // complexity - сложность генерируемой расстановки
    void set_new_model(bool is_rnd, int complexity);

    // установить начальную расстановку
    void set_start_board();

    // совершить шаг назад
    void back_move();

    // проверить возможно ли
    // начать новую игру или сделать шаг назад
    bool check_back_moves_available();

signals:
    void moved();

private:

    // проверить решена ли расстановка
    // если да вывести результат
    void _check_game_end();

    QGridLayout*                _grid;    // layout для кнопок - элементов игры
    BoardModel*                 _model;   // игровая модель
    QVector<FifteenPushButton*> _buttons; // кнопки - элементы игры

private slots:

    // нажата игровая кнопка
    // если возможно совершить перестановку
    // idx - индекс нажатой кнопки
    void _move(int idx);
};

#endif // BOARDVIEW_H
