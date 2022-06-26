/*
 * CIniConfig - read/write *.ini configs class for PDA Maze game.
 *
 * Config variables:
 * +-------------------------------------------------------------------------+
 * | Variable name      | Description           | Values                     |
 * +-------------------------------------------------------------------------+
 * | iniTimerMode       | Game Timer            | up, down                   |
 * | iniMapMode         | Show Map Mode         | all, build, none           |
 * | iniMapSize         | Size Of Map           | 9, 19, 29, 39, 49          |
 * | iniStepShow        | Show Step Counter     | true, false                |
 * | iniScaleScreen     | Set Window Resolution | 160x177, 240x265, 480x531  |
 * | iniSmoothScreen    | Screen Smoothing      | true, false                |
 * | iniAppLang         | App Language          | "en", "ru", "es" and other |
 * +-------------------------------------------------------------------------+
 *
 * Copyright (C) 2014 EXL <exlmotodev@gmail.com>
*/

#ifndef CINICONFIG_H
#define CINICONFIG_H

#include <QObject>
#include <QSettings>

class CIniConfig : public QObject
{
    Q_OBJECT

public:
    explicit CIniConfig(QObject *parent = 0);
    ~CIniConfig();

public:
    enum TTimerModes {
        ETimerUp,
        ETimerDown
    };

    enum TMapModes {
        EMapAll,
        EMapBuild,
        EMapNone
    };

    enum TScaleScreen {
        ERes160x177,
        ERes240x265,
        ERes480x531
    };

    enum TMapSize {
        EMapSize9x9 = 9,
        EMapSize19x19 = 19,
        EMapSize29x29 = 29,
        EMapSize39x39 = 39,
        EMapSize49x49 = 49,
    };

private:
    QSettings *m_Settings;

    int iniTimerMode;
    int iniMapMode;
    int iniMapSize;
    bool iniStepShow;
    int iniScaleScreen;
    bool iniSmoothScreen;
    QString iniAppLang;

    void loadDefaultSettings(void);
    void showAllVariables(void);
    bool checkAllVariables(void);

public:
    bool readIniConfig(void);
    bool writeIniConfig(void);

    void setIniTimerMode(int aTimerMode);
    int getIniTimerMode(void) const;
    void setIniMapMode(int aMapMode);
    int getIniMapMode(void) const;
    void setIniMapSize(int aMapSize);
    int getIniMapSize(void) const;

    void setIniStepShow(bool aStepShow);
    bool getIniStepShow(void) const;
    void setIniScaleScreen(int aScaleScreen);
    int getIniScaleScreen(void) const;
    void setIniSmoothScreen(bool aSmoothScreen);
    bool getIniSmoothScreen(void) const;
    void setIniAppLang(const QString &aAppLang);
    QString getIniAppLang(void) const;
};

#endif // CINICONFIG_H
