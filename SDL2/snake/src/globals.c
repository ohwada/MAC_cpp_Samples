#include "globals.h"

// Game area dimensions
const ushort CELL_SIZE    = 30;

// Game definitions
const double FPS = 60.0;
const char MIN_SPEED = 1;
const char MAX_SPEED = 12;

// Snake colour/gradient count
const ushort SNAKE_GRADIENT_LENGTH = 25;

// Initial snake length
const ushort SNAKE_INIT_LENGTH = 3;

const RGB RAINBOW[6] =
{
    {255, 10, 0},  // Red
    {245, 255, 0}, // Yellow
    {0, 255, 10},  // Green
    {0, 245, 255}, // Light blue
    {10, 0, 255},  // Blue
    {255, 0, 245}  // Violet
};
