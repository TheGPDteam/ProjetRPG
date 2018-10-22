#ifndef AFFICHABLE_H
#define AFFICHABLE_H

#include <SDL/SDL.h>

class Affichable
{

protected:
    SDL_Rect m_rectangle;
public:
    Affichable(SDL_Rect rectangle);
    virtual void afficher() = 0;
    virtual void redimensionner() = 0;
};

#endif // AFFICHABLE_H
