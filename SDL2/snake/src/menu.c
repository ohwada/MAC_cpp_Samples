#include "menu.h"

#include "renderer.h"
#include "globals.h"
#include "game.h"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_rect.h>

#include <math.h>
#include <stdio.h>

// Shared constants
#define STRING_TABLE_LENGTH 6
#define MAX_STRING_LENGTH 15

// TODO:
// The difficulty setting is a little bolted-on
// In the future if there are more settings,
// I should try to separate config from menu

// Structure defining a single element
typedef struct
{
    char displayName[25];
    SDL_Rect area;
    GameState state;
    ushort    value;
} MenuElement;

// Internal variables
static char menuTitle[25];
static MenuElement * pElementArr = NULL;
static uchar maxCount;
static uchar currentCount;
static uchar currentSelection;
static GameState menuType;

// Internal functions
static void MenuAddElement(const MenuElement element);
static void InitialiseMenuElements(void);

// Internal constants
// String table
static const char MENU_STRING_TABLE[STRING_TABLE_LENGTH][MAX_STRING_LENGTH] =
{
    "PLAY",
    "EXIT",
    "MAIN MENU",
    "CONTINUE",
    "DIFFICULTY",
    "BACK"
};

// Enum of index to string in the string table
typedef enum
{
    cStringPlay,
    cStringExit,
    cStringMainMenu,
    cStringContinue,
    cStringDifficulty,
    cStringBack
} StringIndex;

// Maun menu
// String indexes
static const StringIndex MAIN_MENU_STRINGS[] =
{
    cStringPlay,
    cStringExit
};

// Element states
static const GameState MAIN_MENU_STATES[] =
{
    cStateConfig,
    cStateExit
};

// Pause menu
// String indexes
static const StringIndex PAUSE_MENU_STRINGS[] =
{
    cStringContinue,
    cStringMainMenu,
    cStringExit
};

// Element states
static const GameState PAUSE_MENU_STATES[] =
{
    cStatePlay,
    cStateMenu,
    cStateExit
};

// Config menu
// String indexes
static const StringIndex CONFIG_MENU_STRINGS[] =
{
    cStringDifficulty,
    cStringPlay,
    cStringExit
};

// Element states
static const GameState CONFIG_MENU_STATES[] =
{
    cStateValue,
    cStatePlay,
    cStateExit
};

// "Constructor"
// Create menu elements
void MenuInitialise(const GameState initialType)
{
    currentCount     = 0;
    maxCount         = 5;
    currentSelection = 0;
    menuType         = initialType;

    pElementArr = (MenuElement *)calloc(maxCount, sizeof(MenuElement));
    InitialiseMenuElements();
}

// "Destructor"
// Free menu elements
void MenuFree(void)
{
    if(pElementArr)
    {
        free(pElementArr);
        pElementArr = NULL;
    }

    maxCount         = 0;
    currentCount     = 0;
    currentSelection = 0;
    memset(menuTitle, '\0', sizeof(menuTitle));
}

// Update menu based on the keycode
// Return TRUE if selection is made, otherwise return FALSE
// If selection is made (Enter/Return), set the element state variable
BOOL MenuUpdate(const SDL_Keycode keycode, GameState * pState)
{
    switch(keycode)
    {
        case SDLK_UP:
            currentSelection = ((currentSelection - 1) + currentCount) % currentCount;
            break;

        case SDLK_DOWN:
            currentSelection = (currentSelection + 1) % currentCount;
            break;

        case SDLK_LEFT:
            if(pElementArr[currentSelection].state == cStateValue)
            {
                pElementArr[currentSelection].value = fmax(--pElementArr[currentSelection].value, MIN_SPEED);
                GameSetSpeed(pElementArr[currentSelection].value);
            }
            break;

        case SDLK_RIGHT:
            if(pElementArr[currentSelection].state == cStateValue)
            {
                pElementArr[currentSelection].value = fmin(++pElementArr[currentSelection].value, MAX_SPEED);
                GameSetSpeed(pElementArr[currentSelection].value);
            }
            break;

        case SDLK_RETURN:
            if(pElementArr[currentSelection].state != cStateValue)
            {
                *pState = pElementArr[currentSelection].state;
                return TRUE;
            }
            break;

        default:
            break;
    }

    if(menuType == cStatePause && keycode == SDLK_ESCAPE)
    {
        *pState = cStatePlay;
        return TRUE;
    }

    return FALSE;
}

// New new menu state
// If new state is different, free and re-initialise
// otherwise, no op
void MenuSetType(const GameState newState)
{
    if(menuType != newState)
    {
        MenuFree();
        MenuInitialise(newState);
    }
}

// Return the current menu type
GameState MenuGetType(void)
{
    return menuType;
}

// Draw the menu
void MenuDraw(void)
{
    // If pause or game over, draw a semi-transparent background
    if(menuType == cStatePause)
    {
        int windowWidth = 0;
        int windowHeight = 0;
        RendererGetWindowSize(&windowWidth, &windowHeight);

        SDL_Rect r;
        r.x = 0;
        r.y = 0;
        r.w = windowWidth;
        r.h = windowWidth;

        SDL_SetRenderDrawColor(GetRenderer(), 0, 0, 0, 128);
        SDL_RenderFillRect(GetRenderer(), &r);
    }

    SDL_Color colour;
    colour.r = 255;
    colour.g = 255;
    colour.b = 255;
    colour.a = SDL_ALPHA_OPAQUE;

    int windowWidth = 0;
    int windowHeight = 0;
    RendererGetWindowSize(&windowWidth, &windowHeight);
    RendererDrawText(menuTitle, colour, windowWidth / 2, windowHeight / 2, TRUE);

    for(uchar i = 0; i < currentCount; i++)
    {
        colour.g = (i == currentSelection) ? 0 : 255;
        colour.b = (i == currentSelection) ? 0 : 255;
        colour.a = SDL_ALPHA_OPAQUE;
        if(pElementArr[i].state == cStateValue)
        {
            char tmp[30];
            memset(tmp, '\0', sizeof(tmp));
            snprintf(tmp, 30, "<-- %s: %d -->", pElementArr[i].displayName, pElementArr[i].value);
            RendererDrawText(tmp, colour, pElementArr[i].area.x, pElementArr[i].area.y, FALSE);
        }
        else
        {
            RendererDrawText(pElementArr[i].displayName, colour, pElementArr[i].area.x, pElementArr[i].area.y, FALSE);
        }
    }
}

// Add element to the current menu and increment count
static void MenuAddElement(const MenuElement element)
{
    if(currentCount < maxCount)
    {
        pElementArr[currentCount++] = element;
    }
}

// Initialise menu elements
static void InitialiseMenuElements(void)
{
    const StringIndex * pMenuStrings = NULL;
    const GameState   * pMenuStates  = NULL;
    int    menuElementCount = 0;

    switch(menuType)
    {
        case cStateMenu:
            pMenuStrings = MAIN_MENU_STRINGS;
            pMenuStates   = MAIN_MENU_STATES;
            menuElementCount = ARRAY_SIZE(MAIN_MENU_STRINGS);
            strcpy(menuTitle, "Rainbow Snake\0");
            break;

        case cStatePause:
            pMenuStrings = PAUSE_MENU_STRINGS;
            pMenuStates   = PAUSE_MENU_STATES;
            menuElementCount = ARRAY_SIZE(PAUSE_MENU_STRINGS);
            strcpy(menuTitle, "Pause\0");
        break;

        case cStateConfig:
            pMenuStrings = CONFIG_MENU_STRINGS;
            pMenuStates   = CONFIG_MENU_STATES;
            menuElementCount = ARRAY_SIZE(CONFIG_MENU_STRINGS);
            strcpy(menuTitle, "Settings\0");
        break;

        default:
            return;
    }

    int windowWidth = 0;
    int windowHeight = 0;
    RendererGetWindowSize(&windowWidth, &windowHeight);

    int y = (windowHeight / 2);

	for(int i = 0; i < menuElementCount; i++, y += 50)
    {
        MenuElement el;
        el.value = MAX_SPEED / 2;
        memset(el.displayName, '\0', sizeof(el.displayName));
        strcpy(el.displayName, MENU_STRING_TABLE[(int)pMenuStrings[i]]);

        el.area.x = windowWidth / 2;
        el.area.y = y;
        TTF_SizeText(GetFont(), el.displayName, &el.area.w, &el.area.h);
        el.state = pMenuStates[i];
        MenuAddElement(el);
    }
}
