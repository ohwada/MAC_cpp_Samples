// change log
// 2022-06-01 K.OHWADA
// change endl; to Qt::endl


#include "saving_manager.h"
#include "../exceptions/game_exception.h"

#include <QFile>
#include <QDir>
#include <QTextStream>

using namespace battleshipGame;

SavingManager::SavingManager(const QString& fileName) :
    sfile(QFile(fileName)) {}

void SavingManager::load() {
    Settings& settings = Settings::getInstance();
    if (!sfile.exists()) {
        throw GameException("file not exists");
    }
    if (!sfile.open(QFile::ReadOnly)) {
        throw GameException("can not open");
    }
    map<int, int> decksToNumber;
    for (int decks = Settings::MIN_DECKS; decks <= Settings::MAX_DECKS; decks++) {
        decksToNumber[decks] = sfile.readLine().toInt();
    }
    settings.setShipsMap(decksToNumber);
    bool timeLimited = sfile.readLine().toInt();
    settings.setTimeLimited(timeLimited);
    if (timeLimited) {
        int stepDuration = sfile.readLine().toInt();
        settings.setStepDuration(stepDuration);
    }
    sfile.close();
}

void SavingManager::save() {
    Settings& settings = Settings::getInstance();
    if (!sfile.open(QFile::WriteOnly)) {
        throw GameException("can not open to write");
    }
    QTextStream ts(&sfile);
    for (auto [decks, number] : settings.getShipsMap()) {
        // ts << number << endl;
        ts << number << Qt::endl;
    }
    ts << settings.isTimeLimited() << endl;
    if (settings.isTimeLimited()) {
        ts << settings.getStepDuration() << endl;
    }
    sfile.close();
}
