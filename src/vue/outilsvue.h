#ifndef OUTILSVUE_H
#define OUTILSVUE_H

#include <SDL.h>

SDL_Rect initialiserRectangle(int x, int y, int w, int h)
{
    SDL_Rect tmp;
    tmp.x = x;
    tmp.y = y;
    tmp.w = w;
    tmp.h = h;
    return tmp;
}

#endif // OUTILSVUE_H
