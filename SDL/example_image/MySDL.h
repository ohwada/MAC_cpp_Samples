/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// original : https://www.hiroom2.com/2015/05/14/sdl2%E3%81%AEbmp%E7%94%BB%E5%83%8F%E3%81%A8png%E7%94%BB%E5%83%8F%E3%81%AE%E6%8F%8F%E7%94%BB%E5%87%A6%E7%90%86/#sec-2

#ifndef __MYSDL_H
#define __MYSDL_H

namespace mysdl {

#define ARRAYOF(array) (sizeof(array) / sizeof(*array))

#define SDL_PrintError(name)                                    \
  do {                                                          \
    std::cerr << #name << ": " << SDL_GetError() << std::endl;  \
  } while (0)

#define PrintError(error)                                       \
  do {                                                          \
    std::cerr << error << std::endl;                            \
  } while (0)

};

#endif /** __MYSDL_H */
