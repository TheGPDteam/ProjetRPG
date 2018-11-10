#include "zonetexte.h"
#include <iostream>

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
    adapterTexte();
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
        SDL_Rect nouveauRectangle = {m_rectangle.x+(m_rectangle.w-tailleTexte.first)/2,
                                     m_rectangle.y+(m_rectangle.h-tailleTexte.second)/2,
                                     m_rectangle.w,
                                     m_rectangle.h};
        t->redimensionner(nouveauRectangle);
        std::pair<int, int> nouvellePosition = {m_rectangle.x + ((m_rectangle.w - t->obtenirRectTexte().first) / 2),
                                                (m_rectangle.y + (m_rectangle.h + 5 - t->obtenirRectTexte().second) / 2)};
        t->positionner(nouvellePosition);
        m_texteSDL.insert(m_texteSDL.begin(), t);
        break;
    }
    case COMPORTEMENT_TEXTE::SAUT_DE_LIGNE :
    {
        //On regarde mot par mot si le texte rentre dans la zone, sinon on crée un nouveau texte SDL qu'on ajoute au vector
        std::string tmpTexte = m_texte;
        std::string tmpString = "" ;
        for (int i = 0 ; i < tmpTexte.size() ; ++i)
        {
            tmpString += tmpTexte[i];
            if (tmpString.size() * m_taillePolice > m_rectangle.w*1.2)
            {
                while (tmpString.back() != *" ")
                {
                    //Ajout de lettres jusqu'à avoir un espace
                    ++i;
                    tmpString+=tmpTexte[i];
                }
                TexteSDL * t = new TexteSDL(tmpString, m_couleur, m_cheminPolice, m_taillePolice,
                                            std::make_pair<int,int>(m_rectangle.x, m_rectangle.y + ((m_taillePolice+5)*m_texteSDL.size())));
                m_texteSDL.insert(m_texteSDL.end(), t);
                tmpString="";
            }
        }
        //Traitement de la dernière ligne
        if (tmpString.size() > 0)
        {
            TexteSDL * t = new TexteSDL(tmpString, m_couleur, m_cheminPolice, m_taillePolice,
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
