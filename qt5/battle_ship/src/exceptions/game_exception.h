#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H

#include <stdexcept>

using namespace std;

namespace battleshipGame {

/**
 * @brief The GameException class is a class for all game's exceptions.
 */
class GameException : public runtime_error {
public:
    /**
     * Constructor that calls base class constructor.
     * @param msg - message to show.
     */
    GameException(const char* msg) :
        runtime_error(msg) {}
};

}

#endif // GAME_EXCEPTION_H
