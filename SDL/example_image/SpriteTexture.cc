/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// original : https://www.hiroom2.com/2015/05/14/sdl2%E3%81%AEbmp%E7%94%BB%E5%83%8F%E3%81%A8png%E7%94%BB%E5%83%8F%E3%81%AE%E6%8F%8F%E7%94%BB%E5%87%A6%E7%90%86/#sec-2


#include "SpriteTexture.h"

namespace mysdl {

SDL_Surface *
SpriteTexture::createSurfaceFromBMP(const std::string &spriteName)
{
  return SDL_LoadBMP(spriteName.c_str());
}

SDL_Surface *
SpriteTexture::createSurfaceFromPNG(const std::string &spriteName)
{
  SDL_RWops *rwops;
  SDL_Surface *surface;

  rwops = SDL_RWFromFile(spriteName.c_str(), "rb");
  if (rwops == nullptr) {
    SDL_PrintError(SDL_RWFromFile);
    PrintError(spriteName.c_str());
    return nullptr;
  }

  surface = IMG_LoadPNG_RW(rwops);
  SDL_RWclose(rwops);
  return surface;
}

SDL_Surface *
SpriteTexture::createSurface(const std::string &spriteName)
{
  static struct CreateSurfaceFunction create[] = {
    { ".bmp", createSurfaceFromBMP },
    { ".png", createSurfaceFromPNG },
  };

  int start = spriteName.length() - 4;
  if (start <= 0)
    return nullptr;

  std::string name(spriteName, start);;
  for (int index = 0; index < ARRAYOF(create); ++index)
    if (create[index].name == name)
      return create[index].func(spriteName);

  return nullptr;
}

};
