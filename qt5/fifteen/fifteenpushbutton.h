#ifndef FIFTEENPUSHBUTTON_H
#define FIFTEENPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

// элемент игры
class FifteenPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit FifteenPushButton(QWidget *parent = nullptr);

    // поменять отображаеммые номера на кнопках
    static void swap_nums(FifteenPushButton* lhs, FifteenPushButton* rhs) noexcept;

    int get_num() const noexcept;
    void set_num(int num) noexcept;

    int get_idx() const noexcept;
    void set_idx(const int idx) noexcept;

signals:
    void fifteen_btn_clicked(int idx);

private:
    int _num; // отобржаемое число
    int _idx; // индекс элемента - соответствует индексу в модели

    virtual void mousePressEvent(QMouseEvent *e) override;
};

#endif // FIFTEENPUSHBUTTON_H
