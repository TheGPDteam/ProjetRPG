#ifndef AFFICHABLE_H
#define AFFICHABLE_H

#include <SDL/SDL.h>


class Affichable
{

protected:
    SDL_Rect m_rectangle;
public:
    Affichable(SDL_Rect rectangle);
    virtual void afficher(SDL_Surface *surface) = 0;
    virtual void redimensionner(SDL_Rect m_rectangle) = 0;

    SDL_Rect rectangle() const;
    void changerRectangle(SDL_Rect rect);
};

#endif // AFFICHABLE_H
