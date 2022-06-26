#include <iostream>
#include "square.h"

using namespace std;
using namespace battleshipGame;

Square::Square(int x, int y) {
    this->x = x;
    this->y = y;
}

Square Square::makeSquare(int x, int y) {
    Square square(x, y);
    return square;
}

int Square::getX() const {
    return this->x;
}

void Square::setX(int x) {
    this->x = x;
}

int Square::getY() const {
    return this->y;
}

void Square::setY(int y) {
    this->y = y;
}

bool Square::operator==(const Square& square) const {
    return this->x == square.getX() &&
           this->y == square.getY();
}

bool Square::operator!=(const Square& square) const {
    return !(*this == square);
}

Square& Square::operator=(const Square& other) {
    this->x = other.x;
    this->y = other.y;
    return *this;
}
