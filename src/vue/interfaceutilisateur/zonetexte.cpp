#include "zonetexte.h"

ZoneTexte::ZoneTexte(const std::string chemin_police, const int taille_police, const std::pair<int, int> coord_texte, SDL_Rect r,
                     std::string texte, const SDL_Color couleur_texte, COMPORTEMENT_TEXTE ct, ALIGNEMENT_TEXTE at)
    : Affichable(r), m_texte{texte}, m_comportement{ct}, m_alignement{at}, m_cheminPolice{chemin_police}, m_taillePoliceMax{taille_police},
      m_taillePolice{taille_police}, m_coordTexte{coord_texte}, m_couleur{couleur_texte}
{
    adapterTexte();
}

ZoneTexte::~ZoneTexte(){
 for(TexteSDL * t : m_texteSDL)
     delete t;
}

void ZoneTexte::afficher(SDL_Surface *surface_affichage)
{
    for (TexteSDL * t : m_texteSDL)
    {
        t->afficher(surface_affichage);
    }
}

void ZoneTexte::redimensionner(SDL_Rect nouvelleDimension)
{
    m_rectangle = nouvelleDimension;

}

void ZoneTexte::adapterTexte()
{
    for (TexteSDL * t : m_texteSDL)
    {
        delete t;
    }
    switch (m_comportement) {
    case COMPORTEMENT_TEXTE::REDIMENTIONNE :
    {
        //Modification de la taille pour que le texte rentre dans sa zone
        int tailleLettre = m_texte.length()/m_rectangle.w; // A verifier
        TexteSDL * t = new TexteSDL(m_texte, m_couleur, m_cheminPolice, tailleLettre,std::make_pair<int,int>(m_rectangle.x, m_rectangle.y));
        m_texteSDL.insert(m_texteSDL.begin(), t);
        break;
    }
    case COMPORTEMENT_TEXTE::SAUT_DE_LIGNE :
    {
        //On regarde mot par mot si le texte rentre dans la zone, sinon on crée un nouveau texte SDL qu'on ajoute au vector
        break;
    }
    default:
    {

    }
        break;
    }
}
