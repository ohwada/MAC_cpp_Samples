#ifndef BOARD_H
#define BOARD_H

#include "types.h"

typedef enum
{
    cTypeFree  = 0,
    cTypeWall  = 1,
    cTypeSnake = 2,
    cTypeFood  = 3,
} Celltype;

// Main functions
void BoardInitialise(void);
void BoardFree(void);
void BoardDraw(void);

// Helper functions
BOOL BoardIsCellValid(const Point point);
void BoardSetCell(const Point point, const Celltype cell);
Celltype BoardGetCell(const Point point);
BOOL BoardGenerateFood(void);

#endif // !BOARD_H
