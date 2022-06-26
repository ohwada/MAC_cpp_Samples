// change log
// 2022-06-01 K.OHWADA
// #include <QApplication>

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

#include "CIniConfig.h"

// #include <QApplication>
#include <QtWidgets/QApplication>

#include <QDebug>
#include <QFileInfo>

#define INI_CONFIG_NAME "PDA_Maze.ini"
#define INI_CONFIG_GROUP "PDA_Maze"

CIniConfig::CIniConfig(QObject *parent) :
    QObject(parent)
{
    m_Settings = new QSettings(QString(INI_CONFIG_NAME), QSettings::IniFormat);
}

bool CIniConfig::readIniConfig(void)
{
    QFileInfo m_IniFileInfo(INI_CONFIG_NAME);

    if (!(m_IniFileInfo.exists())) {
        qWarning() << "Configuration File" << INI_CONFIG_NAME << "isn't Found!"
                   << "\nDefault configuration will be loaded!";

        loadDefaultSettings();

        return true;
    } else if (!(m_IniFileInfo.isReadable())) {
        qCritical() << "Configuration File" << INI_CONFIG_NAME
                    << "isn't Readable!"
                    << "\nDefault configuration will be loaded!";

        loadDefaultSettings();

        return false;
    } else {
        m_Settings->beginGroup(INI_CONFIG_GROUP);
        iniTimerMode = m_Settings->value("TimerMode").toInt();
        iniMapMode = m_Settings->value("MapMode").toInt();
        iniMapSize = m_Settings->value("MapSize").toInt();
        iniStepShow = m_Settings->value("ShowStep").toBool();
        iniScaleScreen = m_Settings->value("ScaleScreen").toInt();
        iniSmoothScreen = m_Settings->value("SmoothScreen").toBool();
        iniAppLang = m_Settings->value("AppLanguage").toString();
        m_Settings->endGroup();

        showAllVariables();
        if (!checkAllVariables()) {
            loadDefaultSettings();
        }

        return true;
    }
}

void CIniConfig::loadDefaultSettings(void)
{
    iniTimerMode = ETimerUp;        // Timer Up
    iniMapMode = EMapBuild;         // Build Map Mode
    iniMapSize = EMapSize29x29;     // 29x29 Size
    iniStepShow = false;            // Don't show step counter
    iniScaleScreen = ERes160x177;   // Don't scale screen
    iniSmoothScreen = false;        // Don't smooth screen
    iniAppLang = "en";              // English Language

    showAllVariables();
}

void CIniConfig::showAllVariables(void)
{
    qDebug() << "PDA Maze Vars:"
             << "\n-- iniTimerMode =" << iniTimerMode
             << "\n-- iniMapMode =" << iniMapMode
             << "\n-- iniMapSize =" << iniMapSize
             << "\n-- iniStepShow =" << iniStepShow
             << "\n-- iniScaleScreen =" << iniScaleScreen
             << "\n-- iniSmoothScreen =" << iniSmoothScreen
             << "\n-- iniAppLang =" << iniAppLang;
}

bool CIniConfig::checkAllVariables(void)
{
    if (iniTimerMode < ETimerUp || iniTimerMode > ETimerDown) {
        qWarning() << "Incorrect variable:"
                   << "\n-- iniTimerMode = " << iniTimerMode
                   << "\nDefault configuration will be loaded!";
        return false;
    }

    if (iniMapMode < EMapAll || iniMapMode > EMapNone) {
        qWarning() << "Incorrect variable:"
                   << "\n-- iniMapMode = " << iniMapMode
                   << "\nDefault configuration will be loaded!";
        return false;
    }

    if (iniMapSize != EMapSize9x9
            && iniMapSize != EMapSize19x19
            && iniMapSize != EMapSize29x29
            && iniMapSize != EMapSize39x39
            && iniMapSize != EMapSize49x49) {
        qWarning() << "Incorrect variable:"
                   << "\n-- iniMapSize = " << iniMapSize
                   << "\nDefault configuration will be loaded!";
        return false;
    }

    if (iniScaleScreen < ERes160x177 || iniScaleScreen > ERes480x531) {
        qWarning() << "Incorrect variable:"
                   << "\n-- iniScaleScreen = " << iniScaleScreen
                   << "\nDefault configuration will be loaded!";
        return false;
    }

    if (iniAppLang != "en" && iniAppLang != "ru" && iniAppLang != "es") {
        qWarning() << "Incorrect variable:"
                   << "\n-- iniAppLang = " << iniAppLang
                   << "\nDefault configuration will be loaded!";
        return false;
    }

    return true;
}

bool CIniConfig::writeIniConfig(void)
{
    QFileInfo m_IniFileInfo(INI_CONFIG_NAME);

    if (!(m_IniFileInfo.exists())) {
        qWarning() << "Configuration File isn't Found!"
                   << "\nNew configuration file will be created!";
    }

    if (m_IniFileInfo.exists() && !(m_IniFileInfo.isWritable())) {
        qCritical() << "Configuration File isn't writable!";
        return false;
    } else {
        m_Settings->beginGroup(INI_CONFIG_GROUP);
        m_Settings->setValue("TimerMode", iniTimerMode);
        m_Settings->setValue("MapMode",  iniMapMode);
        m_Settings->setValue("MapSize", iniMapSize);
        m_Settings->setValue("ShowStep", iniStepShow);
        m_Settings->setValue("ScaleScreen", iniScaleScreen);
        m_Settings->setValue("SmoothScreen", iniSmoothScreen);
        m_Settings->setValue("AppLanguage", iniAppLang);
        m_Settings->endGroup();
        return true;
    }
}

void CIniConfig::setIniTimerMode(int aTimerMode)
{
    iniTimerMode = aTimerMode;
}

int CIniConfig::getIniTimerMode(void) const
{
    return iniTimerMode;
}

void CIniConfig::setIniMapMode(int aMapMode)
{
    iniMapMode = aMapMode;
}

int CIniConfig::getIniMapMode(void) const
{
    return iniMapMode;
}

void CIniConfig::setIniMapSize(int aMapSize)
{
    iniMapSize = aMapSize;
}

int CIniConfig::getIniMapSize(void) const
{
    return iniMapSize;
}

void CIniConfig::setIniStepShow(bool aStepShow)
{
    iniStepShow = aStepShow;
}

bool CIniConfig::getIniStepShow(void) const
{
    return iniStepShow;
}

void CIniConfig::setIniScaleScreen(int aScaleScreen)
{
    iniScaleScreen = aScaleScreen;
}

int CIniConfig::getIniScaleScreen(void) const
{
    return iniScaleScreen;
}

void CIniConfig::setIniSmoothScreen(bool aSmoothScreen)
{
    iniSmoothScreen = aSmoothScreen;
}

bool CIniConfig::getIniSmoothScreen(void) const
{
    return iniSmoothScreen;
}

void CIniConfig::setIniAppLang(const QString &aAppLang)
{
    iniAppLang = aAppLang;
}

QString CIniConfig::getIniAppLang(void) const
{
    return iniAppLang;
}

CIniConfig::~CIniConfig()
{
    delete m_Settings;
}
