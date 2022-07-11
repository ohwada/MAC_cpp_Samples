#ifndef MENU_H
#define MENU_H

#include "types.h"
#include <SDL2/SDL_keyboard.h>

void MenuInitialise(const GameState initialType);
void MenuFree(void);
BOOL MenuUpdate(const SDL_Keycode keycode, GameState * pState);
void MenuSetType(const GameState newState);
GameState MenuGetType(void);
void MenuDraw(void);

#endif // !MENU_H
