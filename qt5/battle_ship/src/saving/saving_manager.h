#ifndef SAVING_MANAGER_H
#define SAVING_MANAGER_H

#include "settings.h"
#include <QString>
#include <QFile>

namespace battleshipGame {

/**
 * @brief The SavingManager class is used for saving and loading game settings.
 */
class SavingManager {

    QFile sfile; /**< file where settings located */

public:
    /**
     * Deleted constructor.
     */
    SavingManager() = delete;

    /**
     * Constructor that initializes QFile from specified file name.
     * @param fileName - name of the file where settings located.
     */
    SavingManager(const QString& fileName);

    /**
     * Loads settings from the file.
     */
    void load();

    /**
     * Saves settings to the file.
     */
    void save();
};

}

#endif // SAVING_MANAGER_H
