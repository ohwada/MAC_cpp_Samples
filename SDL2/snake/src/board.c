#include "board.h"

#include "globals.h"
#include "renderer.h"

// Internal variables
static Celltype cellArr[BOARD_WIDTH * BOARD_HEIGHT] = { cTypeFree };
static Point freeCellArr[BOARD_WIDTH * BOARD_HEIGHT] = { 0 };
static uchar rainbowTick;

// Internal functions

// Return TRUE if point is within board bounds
// Otherwise, return FALSE
static inline BOOL IsPointInBounds(const Point point)
{
    return (-1 < point.x && point.x < BOARD_WIDTH)
        && (-1 < point.y && point.y < BOARD_HEIGHT);
}

// Convert the point to an array index
static inline short ToIndex(const Point point)
{
    return (point.y * BOARD_WIDTH) + point.x;
}

// Find all free cells and populate 'freeCellArr'
// with their points starting at index 0
//
// Return number of free cells
static uint BoardGetFreeCells(void)
{
    uint count = 0;
    for(ushort x = 0; x < BOARD_WIDTH; x++)
    {
        for(ushort y = 0; y < BOARD_HEIGHT; y++)
        {
            const short INDEX = ToIndex((Point){x, y});
            if(cellArr[INDEX] == cTypeFree)
            {
                freeCellArr[count].x = x;
                freeCellArr[count++].y = y;
            }
        }
    }
    return count;
}

// Public functions

// "Constructor"
// Reset the array elements to 0
void BoardInitialise(void)
{
    memset(cellArr, cTypeFree, sizeof(cellArr));
    memset(freeCellArr, 0, sizeof(cellArr));
    rainbowTick = 0;
}

// "Destructor"
void BoardFree(void)
{
}

// Draw the board
//
// if DEBUG draw the snake cells and grid
void BoardDraw(void)
{
    SDL_Renderer * pRenderer = GetRenderer();
    int windowWidth = 0;
    int windowHeight = 0;
    RendererGetWindowSize(&windowWidth, &windowHeight);

    const int OFFSET_X = (windowWidth / 2) - ((BOARD_WIDTH * CELL_SIZE) / 2);
    const int OFFSET_Y = (windowHeight / 2) - ((BOARD_HEIGHT * CELL_SIZE) / 2);
    const ushort CELL_PADDING = CELL_SIZE / 5;

    // Draw the border around the board
    {
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_Rect r;
        r.x = OFFSET_X - CELL_PADDING;
        r.y = OFFSET_Y - CELL_PADDING;
        r.w = (BOARD_WIDTH * CELL_SIZE) + (CELL_PADDING * 2);
        r.h = (BOARD_HEIGHT * CELL_SIZE) + (CELL_PADDING * 2);
        SDL_RenderFillRect(pRenderer, &r);
    }

    for(ushort x = 0; x < BOARD_WIDTH; x++)
    {
        for(ushort y = 0; y < BOARD_HEIGHT; y++)
        {
            const Celltype CURRENT = BoardGetCell((Point){x, y});
            if(CURRENT == cTypeWall)
            {
                // TODO:
                // This block is currently not used.
                // Will have to be tested
                SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

                // Evil macro function
                // Draw the wall segments for the edges
                // Each wall is 1/5 thickness of the cell
                // This function will calculate the position and
                // orientation of the rectangles
                #define DRAW_CELL(axis, isAxisX, floor, ceiling)\
                do\
                {\
                    if(axis != floor && axis != ceiling) { break; }\
                    \
                    SDL_Rect r;\
                    r.x = x * CELL_SIZE;\
                    r.y = y * CELL_SIZE;\
                    r.w = CELL_SIZE;\
                    r.h = CELL_SIZE;\
                    \
                    if(isAxisX)\
                    {\
                        r.x = (axis == floor) ? axis * CELL_SIZE : (axis * CELL_SIZE) + (CELL_PADDING * 4);\
                        r.w = CELL_PADDING;\
                    }\
                    else\
                    {\
                        r.y = (axis == floor) ? axis * CELL_SIZE : (axis * CELL_SIZE) + (CELL_PADDING * 4);\
                        r.h = CELL_PADDING;\
                    }\
                    r.x += OFFSET_X;\
                    r.y += OFFSET_Y;\
                    SDL_RenderFillRect(pRenderer, &r);\
                }while(FALSE)
                DRAW_CELL(x, TRUE, 0, BOARD_WIDTH - 1);
                DRAW_CELL(y, FALSE, 0, BOARD_HEIGHT - 1);
                #undef DRAW_CELL
                continue;
            }

            if(CURRENT == cTypeFood)
            {
                //SDL_SetRenderDrawColor(pRenderer, 155, 155, 155, SDL_ALPHA_OPAQUE);
                #define MAKE_RGB(x) x.r, x.g, x.b
                SDL_SetRenderDrawColor(pRenderer, MAKE_RGB(RAINBOW[rainbowTick / 10]), SDL_ALPHA_OPAQUE);
                #undef MAKE_RGB
                rainbowTick = (rainbowTick + 1) % (int)FPS;
            }
            #ifdef DEBUG
            else if(CURRENT == cTypeSnake)
            {
                // Draw the cells where the snake is supposed to be on
                SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
            }
            #endif // DEBUG
            else
            {
                SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            }

            SDL_Rect r;
            r.w = CELL_SIZE;
            r.h = CELL_SIZE;
            r.x = OFFSET_X + (x * CELL_SIZE);
            r.y = OFFSET_Y + (y * CELL_SIZE);
            SDL_RenderFillRect(pRenderer, &r);
        }
    }

    // Draw the grid
    #ifdef DEBUG
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for(ushort x = 0; x <= BOARD_WIDTH * CELL_SIZE; x += CELL_SIZE)
    {
        SDL_RenderDrawLine(pRenderer, OFFSET_X + x, OFFSET_Y, OFFSET_X + x, OFFSET_Y + (BOARD_HEIGHT * CELL_SIZE));
    }
    for(ushort y = 0; y <= BOARD_HEIGHT * CELL_SIZE; y += CELL_SIZE)
    {
        SDL_RenderDrawLine(pRenderer, OFFSET_X, OFFSET_Y + y, OFFSET_X + (BOARD_WIDTH * CELL_SIZE), OFFSET_Y + y);
    }
    #endif // DEBUG
}

// Return TRUE if point is within the bounds
// and cell type is either 'free' or 'food'
BOOL BoardIsCellValid(const Point point)
{
    if(IsPointInBounds(point))
    {
        const short INDEX = ToIndex(point);
        return (cellArr[INDEX] == cTypeFree)
            || (cellArr[INDEX] == cTypeFood);
    }
    return FALSE;
}

// Set a cell value at specified point
// If point is out of bounds, ignore
void BoardSetCell(const Point point, const Celltype cell)
{
    if(IsPointInBounds(point))
    {
        cellArr[ToIndex(point)] = cell;
    }
}

// Return cell value at specified point
// If point is out of bounds, return 'wall' type
Celltype BoardGetCell(const Point point)
{
    if(IsPointInBounds(point))
    {
        return cellArr[ToIndex(point)];
    }
    return cTypeWall;
}

// Find all free cells on the board and pick random
// cell to become food cell
// Return TRUE if at least one free cell is found
// Otherwise return FALSE
BOOL BoardGenerateFood(void)
{
    const uint FREE_COUNT = BoardGetFreeCells();
    if(FREE_COUNT == 0)
    {
        return FALSE;
    }
    if(FREE_COUNT == 1)
    {
        BoardSetCell(freeCellArr[0], cTypeFood);
    }
    else
    {
        BoardSetCell(freeCellArr[rand() % FREE_COUNT], cTypeFood);
    }
    return TRUE;
}
