#include "affichable.h"

Affichable::Affichable(SDL_Rect rectangle)
    :m_rectangle{rectangle}
{}

Affichable::~Affichable()
{}

SDL_Rect Affichable::rectangle() const {
    return m_rectangle;
}

void Affichable::changerRectangle(SDL_Rect rect ){
    m_rectangle = rect;
}
