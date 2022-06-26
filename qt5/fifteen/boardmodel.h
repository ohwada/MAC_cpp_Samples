// change log
// 2022-06-01 K.OHWADA
// translated Russian to Englist
// added NONE  to DIRECTION 


#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QVector>
#include <QVariant>
#include <QPair>
#include <QStack>

// game model
class BoardModel {
public:
    // size of the side of the game square
    static constexpr int GAME_SHAPE = 4;

    // field size
    static constexpr int GAME_SIZE = GAME_SHAPE * GAME_SHAPE;

    // empty element
    static constexpr int EMPTY_ELEMENT = 0;

    BoardModel();

    // is_rnd : create a random arrangement or not
    // complexity : complexity of the generated arrangement
    BoardModel(const bool is_rnd, const int complexity);

    // check if the problem is solved
    // if so, return the number of permutations
    QPair<bool, QVariant> is_solved() const noexcept;

    // get field
    const QVector<int>& get_board() const noexcept;

    // check if it's possible
    // start a new game or take a step back
    bool check_back_moves_available() const noexcept;

    // return to original position
    void set_start_board() noexcept;

    // set up a new layout
    void set_new_board(const bool is_rnd, const int complexity);


    // do a permutation
    // if the permutation is done, return
    // index of the empty cell that was swapped
    // idx : index of the element to be rearranged
    QPair<bool, QVariant> move(const int idx);


    // go back one step
    // if successful, then return the indexes of the elements,
    // which are swapped
    QPair<bool, QPair<QVariant, QVariant>> back_move() noexcept;

private:
    enum class DIRECTION {
        NONE = 0,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    // difficulty factor
    static constexpr int _COMPLEXITY_COEF = 10;

    // coefficient of the number of steps to solve the problem
    static constexpr int _SHIFTS_PER_STEP_COEF = 100;


    // count the number of permutations
    // by relative complexity
    static int _compute_actual_complexity(const int complexity);

    // get random direction
    static DIRECTION _gen_direction() noexcept;

    // check if a permutation is possible in this direction
    static bool _check_direction(const int nul_idx, const DIRECTION direction) noexcept;

 
    // check if element is rhs
    // neighbor element at index lhs in this direction
    static bool _check_is_neighbour(const int lhs, const int rhs, const DIRECTION direction) noexcept;

    // make a change if possible
    static bool _make_move(QVector<int>& board, int& nul_idx, const DIRECTION direction) noexcept;

    // get a solved permutation
    static QVector<int> _get_solved_board();


    // check if the placement is solved
    // board : layout to check
    static bool _check_solved(const QVector<int>& board) noexcept;

  
    // generate layout
    // complexity : the complexity of the generated layout
    static QPair<QVector<int>, int> _gen_board(const int num_shifts);


    // helper function for
    // randomization initialization
    void init_random(const int complexity);

    QVector<int>              _board; // arrangement
    int                       _nul_index; // empty element index
    bool                      _is_solved; // is the arrangement resolved?

    QVector<int>              _start_board;  // initial arrangement
    int                       _start_nul_index; // starting index of an empty element
    bool                      _start_is_solved; // whether the initial arrangement is resolved

    int                       _num_shifts; // number of permutations
    QStack<QPair<int, int>>   _states; // permutation history
};

#endif // BOARDMODEL_H
