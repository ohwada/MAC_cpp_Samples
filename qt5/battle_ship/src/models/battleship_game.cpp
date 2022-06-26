#include "battleship_game.h"
#include "battleship_game_ai.h"

using namespace std;
using namespace battleshipGame;

void BattleshipGame::start(const map<int, int>& shipsMap) {
    yourFleet = make_shared<Fleet>();
    opponentFleet = make_shared<Fleet>();
    squareSelected = false;
    shipSize = 1;
    shipHorizontal = true;
    mode = Mode::PLACING;
    shipsLeft = shipsMap;
    stepYours = true;
    BattleshipGameAI::placeShips(*opponentFleet, shipsMap);
    /* for battle mode debug */
    //randomPlacement(*yourFleet);
    //for (auto& [decks, number]: shipsLast) number = 0;
}

BattleshipGame& BattleshipGame::get() {
    static BattleshipGame game;
    return game;
}

void BattleshipGame::finish() {
    yourFleet.reset();
    opponentFleet.reset();
}

Fleet& BattleshipGame::getFleet(bool yours) {
    if (yours) {
        return *yourFleet;
    } else {
        return *opponentFleet;
    }
}
