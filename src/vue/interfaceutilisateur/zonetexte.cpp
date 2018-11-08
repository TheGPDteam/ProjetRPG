#include "zonetexte.h"
#include <iostream>
using namespace std;

ZoneTexte::ZoneTexte(const std::string chemin_police, const int taille_police, const std::pair<int, int> coord_texte, SDL_Rect r,
                     std::string texte, const SDL_Color couleur_texte, COMPORTEMENT_TEXTE ct, ALIGNEMENT_TEXTE at)
    : Affichable(r), m_texte{texte}, m_comportement{ct}, m_alignement{at}, m_cheminPolice{chemin_police}, M_TAILLE_POLICE_MAX{taille_police},
      m_taillePolice{taille_police}, m_coord{coord_texte}, m_couleur{couleur_texte}
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
        int tailleLettre = std::min(M_TAILLE_POLICE_MAX, (int) (m_rectangle.w/m_texte.length())); // A verifier
        TexteSDL * t = new TexteSDL(m_texte, m_couleur, m_cheminPolice, tailleLettre,std::make_pair<int,int>(m_rectangle.x, m_rectangle.y));

        std::pair<int, int > tailleTexte = t->obtenirRectTexte();
        SDL_Rect nouveauRectangle = {m_rectangle.x+(m_rectangle.w-tailleTexte.first)/2,m_rectangle.y+(m_rectangle.h-tailleTexte.second)/2, m_rectangle.w, m_rectangle.h};
        t->redimensionner(nouveauRectangle);
        pair<int, int> nouvellePosition = {m_rectangle.x+(m_rectangle.w-nouveauRectangle.w)/2,
                                           m_rectangle.y+(m_rectangle.h-nouveauRectangle.h)/2};
        t->positionner(nouvellePosition);
        m_texteSDL.insert(m_texteSDL.begin(), t);
        break;
    }
    case COMPORTEMENT_TEXTE::SAUT_DE_LIGNE :
    {
        //On regarde mot par mot si le texte rentre dans la zone, sinon on crée un nouveau texte SDL qu'on ajoute au vector
        std::string copTexte = m_texte;
        while (copTexte.length() != 0)
        {
            std::string tmp = "";

            int i = 0;
            do {
                tmp += copTexte[i];
                ++i;
            } while ((tmp.length() * m_taillePolice) > m_rectangle.w);
            TexteSDL * t = new TexteSDL(tmp, m_couleur, m_cheminPolice, m_taillePolice,
                                        std::make_pair<int,int>(m_rectangle.x, m_rectangle.y + ((m_taillePolice+5)*m_texteSDL.size())));
            m_texteSDL.insert(m_texteSDL.end(), t);
        }
        break;
    }
    default:
    {
        break;
    }
    }
}
