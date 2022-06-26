#include "../models/battleship_game.h"
#include "field_painter.h"

using namespace battleshipGame;

FieldWidget::FieldPainter::FieldPainter(FieldWidget* fw) :
    WidgetPainter(fw), yours(fw->yours) {}

void FieldWidget::FieldPainter::paint() {
    if (yours) QMessageLogger().debug("your fleet updated");
    drawField();
    auto& game = BattleshipGame::get();
    if (game.mode == BattleshipGame::Mode::PLACING) {
        drawPlacing();
    } else {
        drawBattle();
    }
}

void FieldWidget::FieldPainter::drawPlacing() {
    if (!yours) {
        return;
    }
    drawFleet();
    auto& game = BattleshipGame::get();
    if (!game.squareSelected) {
        return;
    }
    auto& yourFleet = game.getFleet(true);
    Ship ship(game.square, game.shipSize, game.shipHorizontal);
    if (game.shipsLeft[game.shipSize] &&
        yourFleet.checkPositionForShip(ship)) {
        drawShip(ship, CORRECT_COLOR);
    } else {
        drawShip(ship , INCORRECT_COLOR);
    }
}

void FieldWidget::FieldPainter::drawBattle() {
    drawFleet();
    drawFleetState();
    auto& game = BattleshipGame::get();
    if (game.mode == BattleshipGame::Mode::RESUME || !game.squareSelected ||
        yours || !game.stepYours) {
        return;
    }
    auto& opponentFleet = game.getFleet(false);
    if (opponentFleet.hasAttacked(game.square)) {
        drawSquare(game.square, INCORRECT_COLOR);
    } else {
        drawSquare(game.square, CORRECT_COLOR);
    }
}

void FieldWidget::FieldPainter::drawFleet() {
    auto& game = BattleshipGame::get();
    auto& fleet = game.getFleet(yours);
    for (auto ship: fleet.getShips()) {
        if (yours || ship.isSunk()) {
            drawShip(ship, SHIP_COLOR);
        }
    }
}

void FieldWidget::FieldPainter::drawFleetState() {
    auto& fleet = BattleshipGame::get().getFleet(yours);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            switch (fleet.getSquareState(i, j)) {
                case Square::ATTACKED: drawSmallPoint(Square(i, j)); break;
                case Square::ATTACKED_WITH_SUCCESS: drawCross(Square(i, j)); break;
                case Square::NOT_ATTACKED:  break;
            }
        }
    }
}

void FieldWidget::FieldPainter::drawShip(Ship ship, QColor color) {
    auto stp = point(ship.getStartSquare());
    auto ssize = ship.getSize();
    painter->setPen(QPen(color, THICK_STROKE));
    painter->setBrush(Qt::NoBrush);
    if (ship.isHorizontal()) {
        painter->drawRect(stp.x(), stp.y(), SQ * ssize, SQ);
    } else {
        painter->drawRect(stp.x(), stp.y(), SQ, SQ * ssize);
    }
}

void FieldWidget::FieldPainter::drawField() {
    const auto SIDE = FieldWidget::SIDE;
    painter->setPen(FIELD_COLOR);
    for (int i = 1; i < 10; i++) {
        painter->drawLine(SQ * i, 0, SQ * i, SIDE);
        painter->drawLine(0, SQ * i, SIDE, SQ * i);
    }
}

void FieldWidget::FieldPainter::drawSquare(Square square, QColor color) {
    painter->setPen(QPen(color, THICK_STROKE));
    painter->setBrush(Qt::NoBrush);
    QPoint lt = point(square);
    painter->drawRect(lt.x(), lt.y(), SQ, SQ);
}

QPoint FieldWidget::FieldPainter::point(Square square) {
    return QPoint(square.getX() * SQ, square.getY() * SQ);
}

void FieldWidget::FieldPainter::drawCross(Square square) {
    auto p = point(square);
    painter->setPen(QPen(ATTACK_COLOR, THICK_STROKE));
    painter->drawLine(p.x(), p.y(), p.x() + SQ, p.y() + SQ);
    painter->drawLine(p.x(), p.y() + SQ, p.x() + SQ, p.y());
}

void FieldWidget::FieldPainter::drawSmallPoint(Square square) {
    auto p = point(square);
    painter->setPen(ATTACK_COLOR);
    painter->setBrush(ATTACK_COLOR);
    painter->drawEllipse(QPoint(p.x() + SQ / 2, p.y() + SQ / 2), 2, 2);
}
