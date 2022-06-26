// change log
// 2022-06-01 K.OHWADA
// added "return DIRECTION::NONE"


#include <QRandomGenerator>
#include <QtMath>

#include "boardmodel.h"

BoardModel::BoardModel()
    : _board(_get_solved_board()),
      _nul_index(GAME_SIZE - 1),
      _is_solved(true),
      _start_board(_board),
      _start_nul_index(_nul_index),
      _start_is_solved(_is_solved),
      _num_shifts(0),
      _states{} {}

BoardModel::BoardModel(const bool is_rnd, const int complexity)
    : BoardModel() {
    if (is_rnd) {
        init_random(complexity);
    }
}

QPair<bool, QVariant> BoardModel::is_solved() const noexcept {
    if (_is_solved) {
        return {true, QVariant(_num_shifts)};
    } else {
        return {false, QVariant()};
    }
}

const QVector<int>& BoardModel::get_board() const noexcept {
    return _board;
}

void BoardModel::set_start_board() noexcept{
    if (_num_shifts != 0) {
        _board      = _start_board;
        _nul_index  = _start_nul_index;
        _is_solved  = _start_is_solved;
        _num_shifts = 0;
        _states.clear();
    }
}

void BoardModel::set_new_board(const bool is_rnd, const int complexity) {
    if (is_rnd) {
        init_random(complexity);
    } else {
        _board           = _get_solved_board();
        _nul_index       = GAME_SIZE - 1;
        _is_solved       = true;

        _start_board     = _board;
        _start_nul_index = _nul_index;
        _start_is_solved = _is_solved;

        _num_shifts      = 0;
        _states.clear();
    }
}

void BoardModel::init_random(const int complexity) {
    const int actual_complexity = _compute_actual_complexity(complexity);
    const int predicted_max_num_shifts = actual_complexity * _SHIFTS_PER_STEP_COEF;

    if (_states.capacity() < predicted_max_num_shifts) {
        _states.reserve(predicted_max_num_shifts);
    }

    bool continue_generating = true;
    while (continue_generating) {
        const auto rnd_result = _gen_board(actual_complexity);
        const auto board      = rnd_result.first;
        const auto nul_index  = rnd_result.second;

        const auto is_solved  = _check_solved(board);
        continue_generating   = is_solved;

        if (!is_solved) {
            _board            = board;
            _nul_index        = nul_index;
            _is_solved        = is_solved;

            _start_board      = _board;
            _start_nul_index  = _nul_index;
            _start_is_solved  = _is_solved;
        }
    }
}

QPair<bool, QVariant> BoardModel::move(const int idx) {
    bool result = false;
    const int swap_idx = _nul_index;

    if (_check_is_neighbour(_nul_index, idx, DIRECTION::UP)) {
        result = _make_move(_board, _nul_index, DIRECTION::UP);
    } else if (_check_is_neighbour(_nul_index, idx, DIRECTION::DOWN)) {
        result = _make_move(_board, _nul_index, DIRECTION::DOWN);
    } else if (_check_is_neighbour(_nul_index, idx, DIRECTION::LEFT)) {
        result = _make_move(_board, _nul_index, DIRECTION::LEFT);
    } else if (_check_is_neighbour(_nul_index, idx, DIRECTION::RIGHT)) {
        result = _make_move(_board, _nul_index, DIRECTION::RIGHT);
    }

    if (result) {
        _is_solved = _check_solved(_board);
        _num_shifts++;
        _states.push({idx, swap_idx});

        return {true, QVariant(swap_idx)};
    } else {
        return {false, QVariant()};
    }
}

QPair<bool, QPair<QVariant, QVariant> > BoardModel::back_move() noexcept {
    if (!_states.empty()) {
        const auto prev = _states.pop();
        qSwap(_board[prev.first], _board[prev.second]);
        _nul_index = prev.second;
        _num_shifts--;
        _is_solved = _check_solved(_board);

        return {true, {QVariant(prev.first), QVariant(prev.second)}};
    } else {
        return {false, {QVariant(), QVariant()}};
    }
}

int BoardModel::_compute_actual_complexity(const int complexity) {
    const int complexity_num = complexity * _COMPLEXITY_COEF;
    return qFloor(complexity_num * qLn(complexity_num));
}

QPair<QVector<int>, int> BoardModel::_gen_board(const int num_shifts) {
    auto final_state = _get_solved_board();
    int nul_index = GAME_SIZE - 1;

    for (int i = 0; i < num_shifts; i++) {
        _make_move(final_state, nul_index, _gen_direction());
    }

    return {final_state, nul_index};
}

bool BoardModel::_check_direction(const int nul_idx, const DIRECTION direction) noexcept {
    if (direction == DIRECTION::UP) {
        return nul_idx > GAME_SHAPE - 1;
    } else if (direction == DIRECTION::DOWN) {
        return nul_idx < GAME_SIZE - GAME_SHAPE;
    } else if (direction == DIRECTION::LEFT) {
        return  nul_idx % GAME_SHAPE != 0;
    } else if (direction == DIRECTION::RIGHT) {
        return nul_idx % GAME_SHAPE != GAME_SHAPE - 1;
    }

    return false;
}

bool BoardModel::_check_is_neighbour(const int lhs, const int rhs, const DIRECTION direction) noexcept {
    switch (direction) {
        case DIRECTION::UP:
             return lhs - GAME_SHAPE == rhs;
        case DIRECTION::DOWN:
            return  lhs + GAME_SHAPE == rhs;
        case DIRECTION::LEFT:
            return lhs - 1 == rhs;
        case DIRECTION::RIGHT:
            return lhs + 1 == rhs;
        default:
            return false;
    }
}

bool BoardModel::_make_move(QVector<int>& board, int& nul_idx, const DIRECTION direction) noexcept {
    if (_check_direction(nul_idx, direction)) {
        if (direction == DIRECTION::UP) {
            qSwap(board[nul_idx], board[nul_idx - GAME_SHAPE]);
            nul_idx -= GAME_SHAPE;
        } else if (direction == DIRECTION::DOWN) {
            qSwap(board[nul_idx], board[nul_idx + GAME_SHAPE]);
            nul_idx += GAME_SHAPE;
        } else if (direction == DIRECTION::LEFT) {
            qSwap(board[nul_idx], board[nul_idx - 1]);
            nul_idx--;
        } else if (direction == DIRECTION::RIGHT) {
            qSwap(board[nul_idx], board[nul_idx + 1]);
            nul_idx++;
        }

        return true;
    } else {
        return false;
    }
}

BoardModel::DIRECTION BoardModel::_gen_direction() noexcept {
    auto gen = QRandomGenerator::global();
    switch (gen->bounded(1, 5)) {
        case 1:
            return DIRECTION::UP;
        case 2:
            return DIRECTION::DOWN;
        case 3:
            return DIRECTION::LEFT;
        case 4:
            return DIRECTION::RIGHT;
    } // switch
    return DIRECTION::NONE;
}


QVector<int> BoardModel::_get_solved_board() {
    QVector<int> final_state(GAME_SIZE);
    for (int i = 0; i < GAME_SIZE; i++) {
        final_state[i] = i + 1;
    }
    final_state[GAME_SIZE - 1] = EMPTY_ELEMENT;

    return final_state;
}

bool BoardModel::_check_solved(const QVector<int>& board) noexcept {
    int num_invs = 0;

    for (int i = 0; i < GAME_SIZE; i++) {
        if (board[i] != (i + 1) % GAME_SIZE) {
            num_invs++;
        }
    }

    return num_invs == 0;
}

bool BoardModel::check_back_moves_available() const noexcept {
    return _num_shifts != 0;
}
