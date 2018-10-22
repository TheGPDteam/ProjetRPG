#ifndef AFFICHABLE_H
#define AFFICHABLE_H


class Affichable
{

protected:
    SDL_Rect m_rectangle;
public:
    Affichable();
    virtual void afficher() = 0;
    virtual void redimensionner() = 0;
};

#endif // AFFICHABLE_H
