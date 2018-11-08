#include "case.h"

Case(SDL_Rect rect, Affichable * donnee)
    : Affichable(rect),
      donne(donnee)
{
    redimensionner(rect);
}

Case::~Case()
{
    delete m_donnee;
}

void Case::afficher(SDL_Surface *surface)
{
    m_donnee->afficher(surface);
}

void Case::redimensionner(SDL_Rect m_rectangle)
{
    donnee->redimensionner(rect);
}

void Case::definirDonnee(Affichable *donnee)
{
    delete m_donnee;
    m_donnee = donnee;
}

void Case::obtenirDonnee() const
{
    return m_donnee;
}
