#pragma once

#include "SDL_pixels.h"

#include <vector>

class Config
{
  public:
    static inline bool isFullscreen = true;
    static inline int  screenWidth  = 1800;
    static inline int  screenHeight = 900;
    static inline int  cellSize     = 12;
    static inline int  navbarHeight = 96;
    static inline int  fontSize     = 15;
    static inline int  upsStep      = 1;

    static inline SDL_Color livingCellColor  = {239, 243, 246, 255};
    static inline SDL_Color livingCellColor2 = {211, 217, 222, 255};
    static inline SDL_Color deadCellColor    = {27, 38, 49, 255};
    static inline SDL_Color deadCellColor2   = {18, 25, 33, 255};

    static inline SDL_Color fontColor       = {27, 38, 49, 255};
    static inline SDL_Color backgroundColor = {239, 243, 246, 255};
};