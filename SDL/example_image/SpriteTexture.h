/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// original : https://www.hiroom2.com/2015/05/14/sdl2%E3%81%AEbmp%E7%94%BB%E5%83%8F%E3%81%A8png%E7%94%BB%E5%83%8F%E3%81%AE%E6%8F%8F%E7%94%BB%E5%87%A6%E7%90%86/#sec-2


#ifndef __MYSDL_SPRITE_TEXTURE_H
#define __MYSDL_SPRITE_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "MySDL.h"
#include "Texture.h"


namespace mysdl {

class SpriteTexture : public Texture {
 private:
  std::string mSpriteName;

  struct CreateSurfaceFunction {
    std::string name;
    SDL_Surface *(*func)(const std::string &);
  };

  static SDL_Surface *createSurfaceFromBMP(const std::string &);
  static SDL_Surface *createSurfaceFromPNG(const std::string &);
  static SDL_Surface *createSurface(const std::string &);

  static SpriteTexture *
  createSpriteTextureFromPNG(const std::string &);
  static SpriteTexture *
  createSpriteTextureFromBMP(const std::string &);

 public:
  SpriteTexture() {}

  SpriteTexture(const std::string &spriteName)
    : mSpriteName(spriteName)
  {
    setSurface(createSurface(spriteName));
  }

  const std::string &getSpriteName() const
  {
    return mSpriteName;
  }
};

};

#endif /** __MYSDL_SPRITE_TEXTURE_H */
