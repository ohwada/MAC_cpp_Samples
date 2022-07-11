#include "snake.h"

#include "globals.h"
#include "renderer.h"

// Internal variables
static Direction directions[2];
static RGB colourArr[SNAKE_COLOUR_COUNT];

static SnakePart * pHead;
static SnakePart * pTail;

// Internal linked-list functions

// Return TRUE if head pointer is NULL
static inline BOOL SnakePartIsEmpty(void)
{
    return !pHead;
}

// Create a new node, with the specified point
// and add to the front of the linked-list
static void SnakePartPushHead(const Point point)
{
    SnakePart * pNewHead = (SnakePart *)calloc(1, sizeof(SnakePart));
    pNewHead->point = point;

    if(SnakePartIsEmpty())
    {
        pTail = pNewHead;
    }
    else
    {
        pHead->pPrev = pNewHead;
    }
    pNewHead->pNext = pHead;
    pHead = pNewHead;
}

// Create a new node, with the specified point
// and add to the back of the linked-list
static void SnakePartPushTail(const Point point)
{
    SnakePart * pNewTail = (SnakePart *)calloc(1, sizeof(SnakePart));
    pNewTail->point = point;

    if(SnakePartIsEmpty())
    {
        pTail = NULL;
    }
    else
    {
        pTail->pNext = pNewTail;
        pNewTail->pPrev = pTail;
    }
    pTail = pNewTail;
}

// Remove the head node from the linked-list and
// set the next node as the head.
// Return the pointer to old head
//
// NOTE: Pointer must be freed
static SnakePart * SnakePartPopHead(void)
{
    SnakePart * pCurrentHead = pHead;
    if(pHead->pNext)
    {
        pHead->pNext->pPrev = NULL;
    }
    else
    {
        pTail = NULL;
    }
    pHead = pHead->pNext;
    return pCurrentHead;
}

// Remove the tail node from the linked-list and
// set the previous node as the tail.
// Return the pointer to old tail
//
// NOTE: Pointer must be freed
static SnakePart * SnakePartPopTail(void)
{
    SnakePart * pCurrentTail = pTail;
    if(pTail->pPrev)
    {
        pTail->pPrev->pNext = NULL;
    }
    else
    {
        pHead = NULL;
    }
    pTail = pTail->pPrev;
    return pCurrentTail;
}

// Delete and free all nodes from the linked-list
static void SnakePartFree(void)
{
    SnakePart * pCurrent = NULL;
    for(pCurrent = pHead; pCurrent;)
    {
        SnakePart * pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        free(pTemp);
        pTemp = NULL;
    }
}

// Calculate the rainbow colours and
// populate the colour array
static void SetColours(void)
{
    // Create the colours
    for(ushort i = 0; i < SNAKE_COLOUR_COUNT; i++)
    {
        RGB rgb;
        rgb.r = 0;
        rgb.g = 0;
        rgb.b = 0;

        const short COLOUR_PICKER = (i % SNAKE_COLOUR_COUNT) / SNAKE_GRADIENT_LENGTH;
        const short MOD_25        = (i % SNAKE_GRADIENT_LENGTH);

        switch(COLOUR_PICKER)
        {
            case 0:
                rgb.r = 255;
                rgb.g = 10 * MOD_25;
                rgb.b = 0;
                break;

            case 1:
                rgb.r = 255 - 10 * MOD_25;
                rgb.g = 255;
                rgb.b = 0;
                break;

            case 2:
                rgb.r = 0;
                rgb.g = 255;
                rgb.b = 10 * MOD_25;
                break;

            case 3:
                rgb.r = 0;
                rgb.g = 255 - 10 * MOD_25;
                rgb.b = 255;
                break;

            case 4:
                rgb.r = 10 * MOD_25;
                rgb.g = 0;
                rgb.b = 255;
                break;

            case 5:
                rgb.r = 255;
                rgb.g = 0;
                rgb.b = 255 - 10 * MOD_25;
                break;
        }
        colourArr[i] = rgb;
    }
}

// Public functions

// "Constructor"
// Set all variables to initial values
void SnakeInitialise(Point initialPoint, const ushort initialLength)
{
    // Reset colour and direction queue arrays
    memset(colourArr, 0, sizeof(colourArr));
    directions[0] = cDirectionRight;
    directions[1] = cDirectionRight;

    // Linked-list nodes
    pHead = NULL;
    pTail = NULL;

    // Populate the colour array
    SetColours();

    // Add the initial snake parts
    SnakePartPushHead(initialPoint);
    for(ushort i = 1; i < initialLength; i++)
    {
        initialPoint.x--;
        SnakePartPushTail(initialPoint);
    }
}

// "Destructor"
// Destroy the linked-list
void SnakeFree(void)
{
    SnakePartFree();
    pHead = NULL;
    pTail = NULL;
}

// Update snake's direction enum and position
void SnakeMove(void)
{
    SnakeUpdateDirection();

    // No point updating the whole snake.
    // Remove the tail and add a new head node.
    SnakePart * pOldTail = SnakePartPopTail();
    if(pOldTail)
    {
        free(pOldTail);
        pOldTail = NULL;
    }
    SnakePartPushHead(SnakeGetNextHeadPoint());
}

// Set the snake's secondary direction enum
// When SnakeMove() is called, primary direction
// will be updated (if valid)
//
// Activate snake if not active
void SnakeSetDirection(const Direction newDirection)
{
    directions[1] = newDirection;
}

// Push new tail node to the linked-list
// The new cell will have the same point as current tail
// Increment snake length
void SnakeAddBodyPart(void)
{
    SnakePartPushTail(pTail->point);
}

// Draw the snake
void SnakeDraw(void)
{
    SDL_Renderer * pRenderer = GetRenderer();
    int windowWidth = 0;
    int windowHeight = 0;
    RendererGetWindowSize(&windowWidth, &windowHeight);

    const int OFFSET_X = (windowWidth / 2) - ((BOARD_WIDTH * CELL_SIZE) / 2);
    const int OFFSET_Y = (windowHeight / 2) - ((BOARD_HEIGHT * CELL_SIZE) / 2);
    ushort i = 0;

    for(SnakePart * pCurrent = pHead; pCurrent; pCurrent = pCurrent->pNext)
    {
        // Set the correct rainbow colour
        #define MAKE_RGB(rgb) rgb.r, rgb.g, rgb.b
        SDL_SetRenderDrawColor(pRenderer, MAKE_RGB(colourArr[i]), SDL_ALPHA_OPAQUE);
        #undef MAKE_RGB

        i = (i + 1) % SNAKE_COLOUR_COUNT;

        // Draw this bit when the snake is longer than 1 cell
        // We have to calculate some rectangles for snake turns and stuff
        if(pCurrent->pNext || pCurrent->pPrev)
        {
            // Evil macro function:
            // Find the difference between points a and b
            // The rectangle should have length 4/5 of the cell centred on the cell
            // If the the difference is positive (i.e. going towards the top-left corner)
            // shift the rectangle by 1/5 cell size towards the origin
            #define DRAW_CELL(a, b)\
                do\
                {\
                    const short PADDING = (CELL_SIZE / 5);\
                    Point diff = a;\
                    diff.x -= b.x;\
                    diff.y -= b.y;\
                    \
                    SDL_Rect r;\
                    r.x = (a.x * CELL_SIZE) + PADDING;\
                    r.y = (a.y * CELL_SIZE) + PADDING;\
                    r.w = PADDING * 4;\
                    r.h = PADDING * 3;\
                    \
                    if(diff.x != 0)\
                    {\
                        r.x = (diff.x == 1) ? r.x - PADDING : r.x;\
                        r.x += OFFSET_X;\
                        r.y += OFFSET_Y;\
                        SDL_RenderFillRect(pRenderer, &r);\
                    }\
                    else if(diff.y != 0)\
                    {\
                        r.w = PADDING * 3;\
                        r.h = PADDING * 4;\
                        r.y = (diff.y == 1) ? r.y - PADDING : r.y;\
                        r.x += OFFSET_X;\
                        r.y += OFFSET_Y;\
                        SDL_RenderFillRect(pRenderer, &r);\
                    }\
                }while(0)

            // For each cell, we draw up to two overlapping rectangles so that
            // we can get either a rectangle with one side = cellsize
            // or an "L" shape where the snake is turning, connecting the next and previous cell
            // This is probably not the most efficient method for drawing since we could
            // draw a single polygon or even a cached shape, but it works so don't touch it
            if(pCurrent->pNext) { DRAW_CELL(pCurrent->point, pCurrent->pNext->point); }
            if(pCurrent->pPrev) { DRAW_CELL(pCurrent->point, pCurrent->pPrev->point); }
            #undef DRAW_CELL
        }
        else // Snake is 1 cell big. Draw a simple square
        {
            SDL_Rect r;
            r.x = OFFSET_X + (pCurrent->point.x * CELL_SIZE) + (CELL_SIZE / 5);
            r.y = OFFSET_Y + (pCurrent->point.y * CELL_SIZE) + (CELL_SIZE / 5);
            r.w = (CELL_SIZE / 5) * 3;
            r.h = (CELL_SIZE / 5) * 3;
            SDL_RenderFillRect(pRenderer, &r);
        }
    }
}

// Return the pointer to the head node
SnakePart * SnakeGetHead(void)
{
    return pHead;
}

// Return the pointer to the tail node
SnakePart * SnakeGetTail(void)
{
    return pTail;
}

// Update snake's direction from the internal queue
// Return TRUE if direction has been updated
BOOL SnakeUpdateDirection(void)
{
    if( abs((char)directions[0] - (char)directions[1]) > 1 )
    {
        directions[0] = directions[1];
        return TRUE;
    }
    return FALSE;
}

// Return snake's next head position
Point SnakeGetNextHeadPoint(void)
{
    if(!pHead)
    {
        const Point EMPTY = {-1, -1};
        return EMPTY;
    }
    Point nextPoint = pHead->point;
    switch(directions[0])
    {
        case cDirectionUp:
            nextPoint.y--;
            break;

        case cDirectionDown:
            nextPoint.y++;
            break;

        case cDirectionLeft:
            nextPoint.x--;
            break;

        case cDirectionRight:
            nextPoint.x++;
            break;

        default:
            break;
    }
    return nextPoint;
}
