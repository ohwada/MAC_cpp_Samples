#ifndef SETTINGS_H
#define SETTINGS_H

#include <map>

using namespace std;

namespace battleshipGame {

/**
 * @brief The Settings class keeps game settings.
 *
 * User can define number of ships for each decks number and
 * duration of human's step. If the step time becomes gone,
 * human player automatically loses.
 * The class uses Singleton design pattern.
 */
class Settings {

    map<int, int> shipsMap; /**< decks to ships map */
    bool timeLimited; /**< is step time limited */
    int stepDuration; /**< duration of a human step */

    /**
      * Default constructor is private.
      */
    Settings() = default;

public:
    static const int
        MIN_DECKS, /**< minimum number of decks */
        MAX_DECKS, /**< maximum number of decks */
        MIN_STEP_DURATION, /**< minimum step duration */
        MAX_STEP_DURATION; /**< maximum step duration */
   static const map<int, int>
        MIN_DECKS_NUMBER, /**< minimum ships number for each decks number */
        MAX_DECKS_NUMBER; /**< maximum ships number for each decks number */

   /**
     * @param shipsMap - ships map to set.
     */
    void setShipsMap(const map<int, int>& shipsMap);

    /**
     * @return Current ships map.
     */
    map<int, int> getShipsMap() const;

    /**
     * @param limited - limited flag to set.
     */
    void setTimeLimited(bool limited);

    /**
     * @return True if time is limited, false otherwise.
     */
    bool isTimeLimited() const;

    /**
     * @param stepDuration - step duration to set.
     */
    void setStepDuration(int stepDuration);

    /**
     * @return Current step duration.
     */
    int getStepDuration() const;

    /**
     * @return Instance of settings.
     */
    static Settings& getInstance();

    /**
     * @return Deleted copy constructor.
     */
    Settings& operator=(Settings&) = delete;

    /**
     * @return Deleted copy constructor.
     */
    Settings& operator=(Settings&&) = delete;
};

}

#endif // SETTINGS_H
