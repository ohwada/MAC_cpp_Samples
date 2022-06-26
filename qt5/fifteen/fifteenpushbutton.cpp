#include <QString>

#include "fifteenpushbutton.h"
#include "boardmodel.h"

FifteenPushButton::FifteenPushButton(QWidget *parent)
    : QPushButton(parent) {}

void FifteenPushButton::swap_nums(FifteenPushButton *lhs, FifteenPushButton *rhs) noexcept {
    const int tmp_num = lhs->_num;
    lhs->set_num(rhs->_num);
    rhs->set_num(tmp_num);
}

int FifteenPushButton::get_num() const noexcept {
    return _num;
}

void FifteenPushButton::set_num(int num) noexcept {
    _num = num;
    if (_num != BoardModel::EMPTY_ELEMENT) {
        setText(QString::number(_num));
        if (!isEnabled()) {
            setEnabled(true);
        }
    } else {
        setText("");
        setEnabled(false);
    }
}

int FifteenPushButton::get_idx() const noexcept {
    return _idx;
}

void FifteenPushButton::set_idx(const int idx) noexcept {
    _idx = idx;
}

// warning: unused parameter 'e' 
void FifteenPushButton::mousePressEvent(QMouseEvent *e) {
    if (_num != BoardModel::EMPTY_ELEMENT) {
        emit fifteen_btn_clicked(_idx);
    }
}
