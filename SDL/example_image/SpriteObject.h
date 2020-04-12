/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// original : https://www.hiroom2.com/2015/05/14/sdl2%E3%81%AEbmp%E7%94%BB%E5%83%8F%E3%81%A8png%E7%94%BB%E5%83%8F%E3%81%AE%E6%8F%8F%E7%94%BB%E5%87%A6%E7%90%86/#sec-2


#ifndef __MYSDL_SPRITE_OBJECT_H
#define __MYSDL_SPRITE_OBJECT_H

#include <SDL.h>

#include "Object.h"
#include "SpriteTexture.h"


namespace mysdl {

class SpriteObject : public Object {
 public:
  SpriteObject(const std::string &name, int x, int y, int w, int h)
    : Object(new SpriteTexture(name), x, y, w, h) {}
};

};

#endif /** __MYSDL_SPRITE_OBJECT_H */
