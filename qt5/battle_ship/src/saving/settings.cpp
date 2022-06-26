#include "settings.h"
#include "../exceptions/game_exception.h"

using namespace battleshipGame;

const int
    Settings::MIN_DECKS = 1,
    Settings::MAX_DECKS = 4,
    Settings::MIN_STEP_DURATION = 5,
    Settings::MAX_STEP_DURATION = 30;

const map<int, int>
    Settings::MIN_DECKS_NUMBER = {{1, 1}, {2, 0}, {3, 0}, {4, 0}},
    Settings::MAX_DECKS_NUMBER = {{1, 4}, {2, 3}, {3, 2}, {4, 1}};

Settings& Settings::getInstance() {
    static Settings settings;
    return settings;
}

void Settings::setShipsMap(const map<int, int>& shipsMap) {
    for (auto [decks, number]: shipsMap) {
        if (decks < MIN_DECKS ||
            decks > MAX_DECKS ||
            number < MIN_DECKS_NUMBER.at(decks) ||
            number > MAX_DECKS_NUMBER.at(decks)) {
            throw GameException("invalid ships map");
        }
    }
    this->shipsMap = shipsMap;
}

map<int, int> Settings::getShipsMap() const {
    return this->shipsMap;
}

void Settings::setTimeLimited(bool timeLimited) {
    this->timeLimited = timeLimited;
}

bool Settings::isTimeLimited() const {
    return this->timeLimited;
}

void Settings::setStepDuration(int stepDuration) {
    if (stepDuration < MIN_STEP_DURATION ||
        stepDuration > MAX_STEP_DURATION) {
        throw GameException("invalid step duration");
    }
    this->stepDuration = stepDuration;
}

int Settings::getStepDuration() const {
    return this->stepDuration;
}
