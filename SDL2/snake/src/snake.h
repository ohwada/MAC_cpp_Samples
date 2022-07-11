#ifndef SNAKE_H
#define SNAKE_H

#include "types.h"

// Direction enum
// Value '2' is skipped to prevent snake from travelling
// in the opposite direction (more in SnakeChangeDirection() function)
typedef enum
{
    cDirectionUp    = 0,
    cDirectionDown  = 1,
    cDirectionLeft  = 3,
    cDirectionRight = 4,
} Direction;

// Snake node as a doubly linked-list
struct SnakePart
{
    Point point;
    struct SnakePart * pPrev;
    struct SnakePart * pNext;
};
typedef struct SnakePart SnakePart;

// Main functions
void SnakeInitialise(Point initialPoint, const ushort initialLength);
void SnakeFree(void);
void SnakeMove(void);
void SnakeSetDirection(const Direction newDirection);
void SnakeAddBodyPart(void);
void SnakeDraw(void);

// Helper functions
ushort SnakeGetLength(void);
SnakePart * SnakeGetHead(void);
SnakePart * SnakeGetTail(void);
BOOL SnakeUpdateDirection(void);
Point SnakeGetNextHeadPoint(void);

#endif // !SNAKE_H
