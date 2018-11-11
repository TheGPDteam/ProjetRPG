#include "tableau.h"
#include "../affichable.h"


Tableau::Tableau(SDL_Rect rect, float hauteur, float largeur, float hauteurLigne, Ligne *enTete)
    :Affichable{rect}, m_hauteur{hauteur}, m_largeur{largeur}, m_hauteurLigne {hauteurLigne}, m_enTete{enTete}
{
}

void Tableau::afficher(SDL_Surface *surface_affichage)
{
    m_enTete->afficher(surface_affichage);
    for (Ligne * l : m_lignes)
    {
        l->afficher(surface_affichage);
    }
}

void Tableau::redimensionner(SDL_Rect nouvelleDimension)
{
    m_rectangle = nouvelleDimension;
    SDL_Rect rectangleParLigne = nouvelleDimension;
    rectangleParLigne.h = rectangleParLigne.h / m_lignes.size();
    for (Ligne * l : m_lignes)
    {
        l->redimensionner(nouvelleDimension);
        rectangleParLigne.y += m_hauteurLigne;
    }
}
