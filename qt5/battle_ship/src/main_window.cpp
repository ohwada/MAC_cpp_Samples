// change log
// 2022-06-01 K.OHWADA
// warning: format string is not a string literal
// warning: 'Background' is deprecated:


#include "main_window.h"
#include "ui_mainwindow.h"
#include "models/battleship_game.h"
#include "models/battleship_game_ai.h"
#include "saving/saving_manager.h"
#include "exceptions/game_exception.h"
#include "widgets/field_widget.h"
#include <QPainter>
#include <QDir>
#include <QTimer>

using namespace battleshipGame;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    savingManager = make_unique<SavingManager>(
        "../BattleshipGame/other/settings.txt");
    try {
        savingManager->load();
    } catch(GameException ex) {
// warning: format string is not a string literal
        QMessageLogger().debug( "%s", ex.what() );
    }

    yourFW = new FieldWidget(true);
    ui->yourFleetLayout->addWidget(yourFW);
    QObject::connect(yourFW, SIGNAL(shipsMapChanged()),
                     this, SLOT(on_shipsMap_changed()));
    yourTimer = new QTimer();
    QObject::connect(yourTimer, SIGNAL(timeout()),
                     this, SLOT(on_yourTimeLeft()));
    opponentFW = new FieldWidget(false);
    ui->opponentFleetLayout->addWidget(opponentFW);
    QObject::connect(opponentFW, SIGNAL(fired(FireResult)),
                     this, SLOT(on_fired(FireResult)));
    opponentTimer = new QTimer();
    QObject::connect(opponentTimer, SIGNAL(timeout()),
                     this, SLOT(on_opponentStep()));
    QObject::connect(this, SIGNAL(fired(FireResult)),
                     this, SLOT(on_fired(FireResult)));
    QObject::connect(this, SIGNAL(gotWinner(bool)),
                     this, SLOT(on_gotWinner(bool)));

    this->setFixedSize(QSize(650, 500));
}

MainWindow::~MainWindow() {
    delete ui;
    delete yourFW;
    delete opponentFW;
    delete yourTimer;
    delete opponentTimer;
}

void MainWindow::resizeEvent(QResizeEvent *e) {
    auto cw = ui->centralWidget;
    int w = cw->width();
    int h = cw->height();
    QPixmap pixmap;
    pixmap.load(":/res/images/main_background.jpg");
    pixmap = pixmap.scaled(w, h, Qt::KeepAspectRatioByExpanding);
    QPalette palette;

// warning: 'Background' is deprecated:
// palette.setBrush(QPalette::Background, pixmap);
    palette.setBrush(QPalette::Window, pixmap);

    cw->setAutoFillBackground(true);
    cw->setPalette(palette);
    QMainWindow::resizeEvent(e);
}

void MainWindow::on_settingsButton_clicked() {
    auto& settings = Settings::getInstance();
    auto shipsMap = settings.getShipsMap();
    ui->d1SpinBox->setValue(shipsMap[1]);
    ui->d2SpinBox->setValue(shipsMap[2]);
    ui->d3SpinBox->setValue(shipsMap[3]);
    ui->d4SpinBox->setValue(shipsMap[4]);
    auto timeLimited = settings.isTimeLimited();
    ui->limitCheckBox->setChecked(timeLimited);
    ui->durationSpinBox->setEnabled(timeLimited);
    if (timeLimited) {
       ui->durationSpinBox->setValue(settings.getStepDuration());
    }
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(2);
}

void MainWindow::on_limitCheckBox_stateChanged(int checked) {
    ui->durationSpinBox->setEnabled(checked);
}

void MainWindow::on_saveReturnButton_clicked() {
    try {
        auto& settings = Settings::getInstance();
        int n1 = ui->d1SpinBox->value();
        int n2 = ui->d2SpinBox->value();
        int n3 = ui->d3SpinBox->value();
        int n4 = ui->d4SpinBox->value();
        settings.setShipsMap({{1, n1}, {2, n2}, {3, n3}, {4, n4}});
        auto timeLimited = ui->limitCheckBox->isChecked();
        settings.setTimeLimited(timeLimited);
        if (timeLimited) {
            settings.setStepDuration(ui->durationSpinBox->value());
        }
    } catch(GameException ex) {
// warning: format string is not a string literal
       QMessageLogger().debug( "%s", ex.what() );
    }
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(0);
}

void MainWindow::closeEvent(QCloseEvent* e) {
    try {
        savingManager->save();
    } catch(GameException ex) {
// warning: format string is not a string literal
         QMessageLogger().debug( "%s", ex.what() );
    }
    QWidget::closeEvent(e);
}

void MainWindow::on_startGameButton_clicked() {
    auto& game = BattleshipGame::get();
    ui->timerLabel->setVisible(Settings::getInstance().isTimeLimited());
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(1);
    auto atw = ui->actionStackedWidget;
    atw->setCurrentIndex(0);
    ui->timerLabel->setText(QString(QChar(0x221E)));
    game.start(Settings::getInstance().getShipsMap());
    on_shipsMap_changed();
}

void MainWindow::on_finishGameButton_clicked() {
    BattleshipGame::get().finish();
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(0);
    opponentTimer->stop();
    yourTimer->stop();
}

void MainWindow::on_shipsMap_changed() {
    QMessageLogger().debug("ships map changed");
    auto d1 = ui->d1RadioButton;
    auto d2 = ui->d2RadioButton;
    auto d3 = ui->d3RadioButton;
    auto d4 = ui->d4RadioButton;
    auto& game = BattleshipGame::get();
    d1->setText(QString("single (") +
        QString::fromStdString(to_string(game.shipsLeft[1])) + ")");
    d2->setText(QString("two (") +
        QString::fromStdString(to_string(game.shipsLeft[2])) + ")");
    d3->setText(QString("three (") +
        QString::fromStdString(to_string(game.shipsLeft[3])) + ")");
    d4->setText(QString("four (") +
        QString::fromStdString(to_string(game.shipsLeft[4])) + ")");
    if (game.shipsLeft[1] == 0) d1->setEnabled(false);
    else d1->setEnabled(true);
    if (game.shipsLeft[2] == 0) d2->setEnabled(false);
    else d2->setEnabled(true);
    if (game.shipsLeft[3] == 0) d3->setEnabled(false);
    else d3->setEnabled(true);
    if (game.shipsLeft[4] == 0) d4->setEnabled(false);
    else d4->setEnabled(true);
    if (game.shipsLeft[game.shipSize]) {
        switch (game.shipSize) {
            case 1: d1->setChecked(true); break;
            case 2: d2->setChecked(true); break;
            case 3: d3->setChecked(true); break;
            case 4: d4->setChecked(true); break;
        }
    } else {
        if (game.shipsLeft[1] != 0) { d1->click(); yourFW->update(); }
        else if (game.shipsLeft[2] != 0) { d2->click(); yourFW->update(); }
        else if (game.shipsLeft[3] != 0) { d3->click(); yourFW->update(); }
        else if (game.shipsLeft[4] != 0) { d4->click(); yourFW->update(); }
    }
    if (!(d1->isEnabled() || d2->isEnabled() || d3->isEnabled() || d4->isEnabled())) {
        game.mode = BattleshipGame::Mode::BATTLE;
        auto atw = ui->actionStackedWidget;
        atw->setCurrentIndex(1);
        yourFW->update();
        QMessageLogger().debug("battle start");
    }
}

void MainWindow::on_d1RadioButton_clicked() {
    BattleshipGame::get().shipSize = 1;
}

void MainWindow::on_d2RadioButton_clicked() {
    BattleshipGame::get().shipSize = 2;
}

void MainWindow::on_d3RadioButton_clicked() {
    BattleshipGame::get().shipSize = 3;
}

void MainWindow::on_d4RadioButton_clicked() {
    BattleshipGame::get().shipSize = 4;
}

void MainWindow::on_fired(FireResult FireResult) {
    auto& game = BattleshipGame::get();
    bool youWon = game.getFleet(false).isDestroyed();
    bool opponentWon = game.getFleet(true).isDestroyed();
    if (youWon || opponentWon) {
        emit gotWinner(youWon);
        return;
    }
    auto tLbl = ui->timerLabel;
    if (FireResult == FireResult::BESIDE) {
        if (!game.stepYours) {
            opponentTimer->stop();
        } else {
            yourTimer->stop();
        }
        game.stepYours = !game.stepYours;
    } else if (game.stepYours) {
        timeLeft = Settings::getInstance().getStepDuration();
        tLbl->setText(QString::number(timeLeft));
    }
    if (!game.stepYours) {
        tLbl->setText(QString(QChar(0x221E)));
        opponentTimer->start(500);
    } else {
        opponentFW->update();
        if (Settings::getInstance().isTimeLimited()) {
            timeLeft = Settings::getInstance().getStepDuration();
            tLbl->setText(QString::number(timeLeft));
            yourTimer->start(1000);
        }
    }
}

void MainWindow::on_opponentStep() {
    auto& game = BattleshipGame::get();
    Square square = BattleshipGameAI::findBestSquare(game.getFleet(true));
    FireResult result = game.getFleet(true).fire(square);
    QMessageLogger().debug("opponent fired");
    yourFW->update();
    emit fired(result);
}

void MainWindow::on_yourTimeLeft() {
    timeLeft--;
    auto tLbl = ui->timerLabel;
    tLbl->setText(QString::number(timeLeft));
    if (timeLeft == 0) {
        yourTimer->stop();
        tLbl->setText("0");
        emit gotWinner(false);
    }
}

void MainWindow::on_gotWinner(bool youWon) {
    opponentTimer->stop();
    yourTimer->stop();
    auto& game = BattleshipGame::get();
    game.mode = BattleshipGame::Mode::RESUME;
    game.youWon = youWon;
    auto atw = ui->actionStackedWidget;
    atw->setCurrentIndex(2);
    auto winLbl = ui->winnerLabel;
    if (youWon) {
        winLbl->setText("Congrats! You are the winner!");
        winLbl->setStyleSheet(
        "background: white; color: green; border: 2px dotted green; padding: 10px");
    } else {
        winLbl->setText("Sorry! Maybe next time!");
        winLbl->setStyleSheet(
        "background: white; color: red; border: 2px dotted red; padding: 10px");
    }
}

void MainWindow::on_restartButton_clicked() {
    on_finishGameButton_clicked();
    on_startGameButton_clicked();
}
