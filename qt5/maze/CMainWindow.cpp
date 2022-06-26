/*
 * CMainWindow - modern Qt GUI class for PDA Maze game.
 *
 * Struction of menu:
 *     |
 *     +-Game
 *     |    |
 *     |    +-New Game <F5>
 *     |    |
 *     |    +-Quit <F10>
 *     |
 *     +-Settings
 *     |    |
 *     |    +-Timer
 *     |    |   |
 *     |    |   +-Timer Up
 *     |    |   |
 *     |    |   +-Timer Down
 *     |    |
 *     |    +-Map
 *     |    |   |
 *     |    |   +-All
 *     |    |   |
 *     |    |   +-Build
 *     |    |   |
 *     |    |   +-None
 *     |    |
 *     |    +-Size of map
 *     |    |   |
 *     |    |   +-9x9
 *     |    |   |
 *     |    |   +-19x19
 *     |    |   |
 *     |    |   +-29x29
 *     |    |   |
 *     |    |   +-39x39
 *     |    |   |
 *     |    |   +-49x49
 *     |    |
 *     |    +-Step Counter
 *     |    |
 *     |    +-Screen Size
 *     |    |   |
 *     |    |   +-160x177
 *     |    |   |
 *     |    |   +-240x265
 *     |    |   |
 *     |    |   +-480x531
 *     |    |
 *     |    +-Language
 *     |        |
 *     |        +-English
 *     |        |
 *     |        +-Spanish
 *     |        |
 *     |        +-Russian
 *     |
 *     +-Help
 *          |
 *          +-Control Keys <F1>
 *          |
 *          +-About PDA Maze
 *          |
 *          +-About Qt...
 *
 * Copyright (C) 2014 EXL <exlmotodev@gmail.com>
 */

#include "CMainWindow.h"

#include <QApplication>
#include <QCloseEvent>
#include <QDebug>
#include <QDir>
#include <QMenuBar>

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /* Install translations for App */
    qApp->installTranslator(&m_AppTranslator);

    m_IniConfig = new CIniConfig(this);
    m_PlayField = new CPlayField(this);

    if (!(m_IniConfig->readIniConfig())) {
        qCritical() << "Error reading config!";
    }

    m_PlayField->setTimerMode(m_IniConfig->getIniTimerMode());
    m_PlayField->setMapMode(m_IniConfig->getIniMapMode());
    m_PlayField->setMapSize(m_IniConfig->getIniMapSize());
    m_PlayField->setStepStatus(m_IniConfig->getIniStepShow());
    m_PlayField->setScaleScreen(m_IniConfig->getIniScaleScreen());
    m_PlayField->setSmoothScreen(m_IniConfig->getIniSmoothScreen());
    m_PlayField->setAppLang(m_IniConfig->getIniAppLang());

    createActions();
    m_actionShowStep->setChecked(m_IniConfig->getIniStepShow());
    if (m_IniConfig->getIniScaleScreen() != CIniConfig::ERes160x177) {
        m_actionSmoothScreen->setChecked(m_IniConfig->getIniSmoothScreen());
    } else {
        disableSmoothScreen();
    }

    createMenus();

    loadTranslations();

    retranslateUi();

    setCentralWidget(m_PlayField);
    detFixedSize(m_IniConfig->getIniScaleScreen());
    setWindowIcon(QIcon("://icons/PDA_maze_64x64.png"));
}

void CMainWindow::createActions(void)
{
    m_actionNewGame = new QAction(this);
    m_actionNewGame->setShortcut(Qt::Key_F5);
    connect(m_actionNewGame, SIGNAL(triggered()),
            m_PlayField, SLOT(startGame()));

    m_actionQuit = new QAction(this);
    m_actionQuit->setShortcut(Qt::Key_F10);
    connect(m_actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    m_actionShowStep = new QAction(this);
    m_actionShowStep->setCheckable(true);
    connect(m_actionShowStep, SIGNAL(triggered(bool)),
            this, SLOT(slotShowStepChange(bool)));

    m_actionSmoothScreen = new QAction(this);
    m_actionSmoothScreen->setCheckable(true);
    connect(m_actionSmoothScreen, SIGNAL(triggered(bool)),
            this, SLOT(slotSmoothScreenChange(bool)));

    m_actionHelp = new QAction(this);
    m_actionHelp->setShortcut(Qt::Key_F1);
    connect(m_actionHelp, SIGNAL(triggered()), m_PlayField, SLOT(showHelp()));

    m_actionAbout = new QAction(this);
    connect(m_actionAbout, SIGNAL(triggered()), m_PlayField, SLOT(stopGame()));

    m_actionAboutQt = new QAction(this);
    connect(m_actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void CMainWindow::createMenus(void)
{
    m_menuFile = new QMenu(this);
    m_menuFile->addAction(m_actionNewGame);
    m_menuFile->addSeparator();
    m_menuFile->addAction(m_actionQuit);

    m_menuSettings = new QMenu(this);
    m_menuSettings->addMenu(createTimerMenu());
    m_menuSettings->addMenu(createMapModeMenu());
    m_menuSettings->addMenu(createMapSizeMenu());
    m_menuSettings->addSeparator();
    m_menuSettings->addAction(m_actionShowStep);
    m_menuSettings->addSeparator();
    m_menuSettings->addMenu(createScaleScreenMenu());
    m_menuSettings->addSeparator();
    m_menuSettings->addMenu(createLanguageMenu());

    m_menuHelp = new QMenu(this);
    m_menuHelp->addAction(m_actionHelp);
    m_menuHelp->addSeparator();
    m_menuHelp->addAction(m_actionAbout);
    m_menuHelp->addAction(m_actionAboutQt);

    menuBar()->addMenu(m_menuFile);
    menuBar()->addMenu(m_menuSettings);
    menuBar()->addMenu(m_menuHelp);
}

QMenu *CMainWindow::createTimerMenu(void)
{
    m_menupTimer = new QMenu(this);

    m_actionGroupTimer = new QActionGroup(this);
    connect(m_actionGroupTimer, SIGNAL(triggered(QAction *)),
            this, SLOT(slotTimerModeChange(QAction *)));

    for (int i = CIniConfig::ETimerUp; i <= CIniConfig::ETimerDown; ++i) {
        m_actionTimer = new QAction(this);
        m_actionTimer->setCheckable(true);
        m_actionTimer->setData(i);

        m_menupTimer->addAction(m_actionTimer);
        m_actionGroupTimer->addAction(m_actionTimer);

        if (i == m_IniConfig->getIniTimerMode()) {
            m_actionTimer->setChecked(true);
        }
    }

    return m_menupTimer;
}

QMenu *CMainWindow::createMapModeMenu(void)
{
    m_menupMapMode = new QMenu(this);

    m_actionGroupMapMode = new QActionGroup(this);
    connect(m_actionGroupMapMode, SIGNAL(triggered(QAction *)),
            this, SLOT(slotMapModeChange(QAction *)));

    for (int i = CIniConfig::EMapAll; i <= CIniConfig::EMapNone; ++i) {
        m_actionMapMode = new QAction(this);
        m_actionMapMode->setCheckable(true);
        m_actionMapMode->setData(i);

        m_menupMapMode->addAction(m_actionMapMode);
        m_actionGroupMapMode->addAction(m_actionMapMode);

        if (i == m_IniConfig->getIniMapMode()) {
            m_actionMapMode->setChecked(true);
        }
    }

    return m_menupMapMode;
}

QMenu *CMainWindow::createMapSizeMenu(void)
{
    m_menupMapSize = new QMenu(this);

    m_actionGroupMapSize = new QActionGroup(this);
    connect(m_actionGroupMapSize, SIGNAL(triggered(QAction *)),
            this, SLOT(slotMapSizeChange(QAction *)));

    for (int i = CIniConfig::EMapSize9x9;
         i <= CIniConfig::EMapSize49x49; i+=10) {
        m_actionMapSize = new QAction(this);
        m_actionMapSize->setCheckable(true);
        m_actionMapSize->setData(i);

        m_menupMapSize->addAction(m_actionMapSize);
        m_actionGroupMapSize->addAction(m_actionMapSize);

        if (i == m_IniConfig->getIniMapSize()) {
            m_actionMapSize->setChecked(true);
        }
    }

    return m_menupMapSize;
}

QMenu *CMainWindow::createScaleScreenMenu(void)
{
    m_menupScaleScreen = new QMenu(this);

    m_actionGroupScaleScreen = new QActionGroup(this);
    connect(m_actionGroupScaleScreen, SIGNAL(triggered(QAction*)),
            this, SLOT(slotScaleScreenChange(QAction *)));

    for (int i = CIniConfig::ERes160x177; i <= CIniConfig::ERes480x531; ++i) {
        m_actionScaleScreen = new QAction(this);
        m_actionScaleScreen->setCheckable(true);
        m_actionScaleScreen->setData(i);

        m_menupScaleScreen->addAction(m_actionScaleScreen);
        m_actionGroupScaleScreen->addAction(m_actionScaleScreen);

        if (i == m_IniConfig->getIniScaleScreen()) {
            m_actionScaleScreen->setChecked(true);
        }
    }

    m_menupScaleScreen->addSeparator();
    m_menupScaleScreen->addAction(m_actionSmoothScreen);

    return m_menupScaleScreen;
}

QMenu *CMainWindow::createLanguageMenu(void)
{
    m_menupAppLang = new QMenu(this);

    m_actionGroupAppLang = new QActionGroup(this);
    connect(m_actionGroupAppLang, SIGNAL(triggered(QAction *)),
            this, SLOT(slotSwitchLanguage(QAction*)));

    QDir qmDir("://i18n/");
    QStringList fileNames = qmDir.entryList(QStringList("PDA_Maze_*.qm"));

    for (int i = 0; i < fileNames.size(); ++i) {
        QString locale = fileNames[i];
        locale.remove(0, locale.indexOf('_') + 1);
        locale.remove("Maze_");
        locale.chop(3);

        QTranslator translator;
        translator.load(fileNames[i], qmDir.absolutePath());

        QString language;
        if (locale == "en") {
            language = "English";
        } else if (locale == "ru") {
            language = "Russian";
        } else if (locale == "es") {
            language = "Spanish";
        }

        m_actionAppLang = new QAction(QString("&%1").arg(language), this);
        m_actionAppLang->setCheckable(true);
        m_actionAppLang->setIcon(QIcon(QString("://icons/")
                                       + locale + QString(".png")));
        m_actionAppLang->setData(locale);

        m_menupAppLang->addAction(m_actionAppLang);
        m_actionGroupAppLang->addAction(m_actionAppLang);

        if (locale == m_IniConfig->getIniAppLang()) {
            m_actionAppLang->setChecked(true);
        } else if (m_IniConfig->getIniAppLang() == "" && locale == "en") {
            m_actionAppLang->setChecked(true);
        }
    }

    return m_menupAppLang;
}

void CMainWindow::disableSmoothScreen(void)
{
    m_actionSmoothScreen->setChecked(false);
    m_actionSmoothScreen->setDisabled(true);
    m_IniConfig->setIniSmoothScreen(false);
    qWarning() << "Smooth screen function are disabled.";
}

void CMainWindow::loadTranslations(void)
{
    QDir qmDir("://i18n");
    QString qmPath = qmDir.absolutePath();

    m_AppTranslator.load("PDA_Maze_" + m_IniConfig->getIniAppLang(), qmPath);
}

void CMainWindow::retranslateUi(void)
{
    m_actionGroupTimer->actions().at(CIniConfig::ETimerUp)
            ->setText(tr("Timer Up"));
    m_actionGroupTimer->actions().at(CIniConfig::ETimerDown)
            ->setText(tr("Timer Down"));

    m_actionGroupMapMode->actions().at(CIniConfig::EMapAll)
            ->setText(tr("All"));
    m_actionGroupMapMode->actions().at(CIniConfig::EMapBuild)
            ->setText(tr("Build"));
    m_actionGroupMapMode->actions().at(CIniConfig::EMapNone)
            ->setText(tr("None"));

    for (int i = 0; i < 5; ++i) {
        m_actionGroupMapSize->actions().at(i)
                ->setText(tr("%1x%1").arg(i * 10 + 9));
    }

    m_actionGroupScaleScreen->actions().at(CIniConfig::ERes160x177)
            ->setText(tr("160x177"));
    m_actionGroupScaleScreen->actions().at(CIniConfig::ERes240x265)
            ->setText(tr("240x265"));
    m_actionGroupScaleScreen->actions().at(CIniConfig::ERes480x531)
            ->setText(tr("480x531"));

    m_actionNewGame->setText(tr("&New Game"));
    m_actionQuit->setText(tr("&Quit"));
    m_actionShowStep->setText(tr("&Step Counter"));
    m_actionSmoothScreen->setText(tr("Smooth"));
    m_actionHelp->setText(tr("&Control Keys"));
    m_actionAbout->setText(tr("&About"));
    m_actionAboutQt->setText(tr("About &Qt..."));
    m_menupTimer->setTitle(tr("&Timer"));
    m_menupMapMode->setTitle(tr("&Map"));
    m_menupMapSize->setTitle(tr("Si&ze"));
    m_menupScaleScreen->setTitle(tr("S&creen Size"));
    m_menuFile->setTitle(tr("&Game"));

    m_menupAppLang->setTitle(tr("&Language"));
    m_menuHelp->setTitle(tr("&Help"));

    switch (m_IniConfig->getIniScaleScreen()) {
    case CIniConfig::ERes240x265:
    case CIniConfig::ERes480x531:
        m_menuSettings->setTitle(tr("&Settings"));
        setWindowTitle(tr("PDA Maze"));
        break;
    case CIniConfig::ERes160x177:
    default: // Russian menu length fix on 160x200
        m_menuSettings->setTitle(tr("&Settings-short."));
        setWindowTitle(tr("Maze"));
        break;
    }

    qDebug() << "Retranslate MainWindow, Lang:"
             << m_IniConfig->getIniAppLang();

    m_PlayField->retranslateUi();
}

void CMainWindow::detFixedSize(int aScreenScale)
{
    int heightMenuBar = menuBar()->sizeHint().height();

    switch (aScreenScale) {
    case CIniConfig::ERes240x265:
        m_PlayField->setFixedSize(240, 265);
        setFixedSize(240, 265 + heightMenuBar);
        break;
    case CIniConfig::ERes480x531:
        m_PlayField->setFixedSize(480, 531);
        setFixedSize(480, 531 + heightMenuBar);
        break;
    case CIniConfig::ERes160x177:
    default: // adjustSize() isn't working correctly
        m_PlayField->setFixedSize(160, 177);
        setFixedSize(160, 177 + heightMenuBar);
        break;
    }
}

void CMainWindow::slotTimerModeChange(QAction *action)
{
    m_IniConfig->setIniTimerMode(action->data().toInt());
    m_PlayField->setTimerMode(action->data().toInt());
    qDebug() << "Changed TimerMode:" << action->data().toInt();
}

void CMainWindow::slotMapModeChange(QAction *action)
{
    m_IniConfig->setIniMapMode(action->data().toInt());
    m_PlayField->setMapMode(action->data().toInt());
    qDebug() << "Changed MapMode:" << action->data().toInt();
}

void CMainWindow::slotMapSizeChange(QAction *action)
{
    m_IniConfig->setIniMapSize(action->data().toInt());
    m_PlayField->setMapSize(action->data().toInt());
    qDebug() << "Changed MapSize:" << action->data().toInt();
}

void CMainWindow::slotScaleScreenChange(QAction *action)
{
    m_IniConfig->setIniScaleScreen(action->data().toInt());

    switch (m_IniConfig->getIniScaleScreen()) {
    case CIniConfig::ERes160x177:
        disableSmoothScreen();
        break;
    default:
        m_actionSmoothScreen->setEnabled(true);
        break;
    }

    m_PlayField->setScaleScreen(m_IniConfig->getIniScaleScreen());
    detFixedSize(m_IniConfig->getIniScaleScreen());

    retranslateUi(); // Change Window Title

    qDebug() << "Changed ScreenScale:" << m_IniConfig->getIniScaleScreen();
}

void CMainWindow::slotShowStepChange(bool aShowStep)
{
    m_IniConfig->setIniStepShow(aShowStep);
    m_PlayField->setStepStatus(aShowStep);
    qDebug() << "Changed ShowStep:" << aShowStep;
}

void CMainWindow::slotSmoothScreenChange(bool aSmoothScreen)
{
    m_IniConfig->setIniSmoothScreen(aSmoothScreen);
    m_PlayField->setSmoothScreen(aSmoothScreen);
    qDebug() << "Changed ScreenSmooth:" << aSmoothScreen;
}

void CMainWindow::slotSwitchLanguage(QAction *action)
{
    QString locale = action->data().toString();

    m_IniConfig->setIniAppLang(locale);

    QDir qmDir("://i18n");
    QString qmPath = qmDir.absolutePath();

    m_AppTranslator.load("PDA_Maze_" + locale, qmPath);

    m_PlayField->setAppLang(locale);

    retranslateUi();
}

void CMainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "Writing config...";
    m_IniConfig->writeIniConfig();
    qDebug() << "Quiting...";
    event->accept();
}

CMainWindow::~CMainWindow()
{
    /* Empty Destructor */
}
