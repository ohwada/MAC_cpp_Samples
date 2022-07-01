// BadproG.com
#ifndef MOVING_SHAPE_1_IMOVABLE_H
#define MOVING_SHAPE_1_IMOVABLE_H

class IMovable {
public:
    enum Direction {
        kDirectionDown,
        kDirectionRight,
        kDirectionLeft,
        kDirectionUp
    };

public:
    virtual ~IMovable() {}
    virtual void move(Direction) = 0;
};

#endif // MOVING_SHAPE_1_IMOVABLE_H
