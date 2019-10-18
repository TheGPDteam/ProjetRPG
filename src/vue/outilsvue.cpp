#include "outilsvue.h"

SDL_Rect initialiserRectangle(int x, int y, int largeur, int hauteur) {
    SDL_Rect tmp;
    tmp.x = x;
    tmp.y = y;
    tmp.w = largeur;
    tmp.h = hauteur;
    return tmp;
}
