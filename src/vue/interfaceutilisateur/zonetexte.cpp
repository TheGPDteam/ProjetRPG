#include "zonetexte.h"

ZoneTexte::ZoneTexte(const std::string chemin_police, const int taille_police, const std::pair<int, int> coord_texte,
                     std::string texte, const SDL_Color couleur_texte, COMPORTEMENT_TEXTE ct, ALIGNEMENT_TEXTE at)
    : m_texte{texte}, m_comportement{ct}, m_alignement{at}
{
    initialiserTexte();
}

ZoneTexte::~ZoneTexte(){
 for(auto t : m_texte)
     delete t;
}

void ZoneTexte::afficher(SDL_Surface *surface_affichage, SDL_Rect zoneTexte, string texte)
{

}

void ZoneTexte::redimensionner(SDL_Rect nouvelleDimension, string texte)
{

}
