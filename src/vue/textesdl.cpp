#include "textesdl.h"

std::map<int, TTF_Font*> TexteSDL::m_fonts= {};


//!
//! \brief Constructeur paramétré d'un texte
//! \author pgutierrez
//! \date 11/11/16
//! @param texte texte à afficher sur la fenetre d'affichage
//! @param couleur_texte couleur du texte à afficher sur la fenetre d'affichage
//! @param chemin_police chemin de la police du texte à afficher sur la fenetre d'affichage
//! @param taille_police taille de la police du texte à afficher sur la fenetre d'affichage
//! @param coord_texte coordonnées du texte dans la fenetre d'affichage
//! \version 0.1
//!
//! Initialise un texte SDL avec sa taille, sa police et son emplacement
//!
TexteSDL::TexteSDL(const std::string texte, const SDL_Color couleur_texte, const std::string chemin_police, const int taille_police,
                   const std::pair<int, int> coord_texte)
{
    if(TTF_Init() == -1)
    {
        std::cout << "Erreur d'initialisation de TTF_Init" << std::endl;
        TTF_Quit();
    }

    if(m_fonts.find(taille_police)== m_fonts.end())
        m_fonts[taille_police] = TTF_OpenFont(chemin_police.c_str(), taille_police);

    m_policeTexte = m_fonts.at(taille_police);

    if(m_policeTexte == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
    }

    m_texteStr = texte;

    m_couleurTexte = couleur_texte;

    m_texte = TTF_RenderText_Blended(m_policeTexte, texte.c_str(), m_couleurTexte);

    m_positionTexte.x = coord_texte.first;
    m_positionTexte.y = coord_texte.second;
}




//!
//! \brief Constructeur paramétré d'un texte
//! \author pgutierrez
//! \date 11/11/16
//! @param texte texte à afficher sur la fenetre d'affichage
//! @param couleur_texte couleur du texte à afficher sur la fenetre d'affichage
//! @param chemin_police chemin de la police du texte à afficher sur la fenetre d'affichage
//! @param taille_police taille de la police du texte à afficher sur la fenetre d'affichage
//! @param coord_rectangle coordonnées du rectangle correspondant au texte
//! @param taille_rectangle taille du rectangle correspondant au texte
//! \version 0.3
//!
//! Initialise un texte SDL avec sa taille, sa police et son emplacement en le centrant par rapport à un rectangle
//!

TexteSDL::TexteSDL(const std::string texte, const SDL_Color couleur_texte, const std::string chemin_police, const int taille_police,
                   const std::pair<int, int> coord_rectangle, const std::pair<int, int> taille_rectangle)
    : TexteSDL(texte, couleur_texte, chemin_police, taille_police, coord_rectangle)
{
    m_positionTexte.x = (coord_rectangle.first + (taille_rectangle.first/2)) - (m_texte->w/2);
    m_positionTexte.y = (coord_rectangle.second + (taille_rectangle.second/2)) - (m_texte->h/2);
}



//!
//! \brief Affiche un texte
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
//!
//! Affichage du texte dans la fenêtre d'affichage
//!

void TexteSDL::afficherTexte(SDL_Surface* surface_affichage)
{
    SDL_BlitSurface(m_texte, nullptr, surface_affichage, &m_positionTexte);
}

//!
//! \brief Mise à jour du contenu texte à afficher
//! \author fvain
//! \param nouveauTexte le nouveau texte à afficher
//! \version 0.1
//!
//! Mise à jour du texte
//!
void TexteSDL::mettreAJourTexte(std::string nouveauTexte)
{
  m_texteStr = nouveauTexte;
  m_texte = TTF_RenderText_Blended(m_policeTexte, nouveauTexte.c_str(), m_couleurTexte);
}


std::string TexteSDL::getTexteStr() const
{
    return m_texteStr;
}

int TexteSDL::getHauteurFont() const
{
    if (m_texte != nullptr)
    {
        return m_texte->h;
    }

    return 0;
}


//!
//! \brief Destructeur d'un texte
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
//!
//! Detruit le SDL_Surface servant à afficher le texte si il est initialisé
//!

TexteSDL::~TexteSDL()
{
    if(m_texte != nullptr)
    {
        SDL_FreeSurface(m_texte);
    }
}
