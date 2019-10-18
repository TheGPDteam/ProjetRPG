#include "textesdl.h"
#include "ressources/policetexte.h"
#include <iostream>

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
TexteSDL::TexteSDL(const std::string texte, const SDL_Color &couleur_texte, const std::string chemin_police, const int taille_police,
                   const std::pair<int, int> coord_texte)
    : Affichable({coord_texte.first, coord_texte.second})
{

    if (TTF_Init() == -1){
        std::cerr << "Erreur d'initialisation de TTF_Init" << std::endl;
        TTF_Quit();
    }

    if (m_fonts.find(taille_police)== m_fonts.end())  m_fonts[taille_police] = TTF_OpenFont(chemin_police.c_str(), taille_police);

    m_policeTexte = m_fonts.at(taille_police);
    if (m_policeTexte == nullptr){
        std::cerr << SDL_GetError() << std::endl;
    }

    m_texteStr = texte;
    m_couleurTexte = couleur_texte;
    m_texte = TTF_RenderText_Blended(m_policeTexte, texte.c_str(), m_couleurTexte);
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

TexteSDL::TexteSDL(const std::string texte, const SDL_Color & couleur_texte, const std::string chemin_police, const int taille_police,
                   const std::pair<int, int> coord_rectangle, const std::pair<int, int> taille_rectangle)
    : TexteSDL(texte, couleur_texte, chemin_police, taille_police, coord_rectangle)

{
    SDL_Rect position = {
        .x = (coord_rectangle.first + (taille_rectangle.first/2)) - (m_texte->w/2),
        .y = (coord_rectangle.second + (taille_rectangle.second/2)) - (m_texte->h/2)
    };
    m_rectangle = position;
}



//!
//! \brief Affiche un texte
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
//!
//! Affichage du texte dans la fenêtre d'affichage
//!

void TexteSDL::afficher(SDL_Surface* surface_affichage){
    SDL_BlitSurface(m_texte, nullptr, surface_affichage, &m_rectangle);
}


void TexteSDL::redimensionner(SDL_Rect nouvelle_dimension) {
    m_rectangle = nouvelle_dimension;
    std::pair<int, int > tailleTexte = obtenirRectTexte();
    tailleTexte.first*=1.4;
    tailleTexte.second*=1.4;

    float ratio_largeur  = tailleTexte.first * 1. / m_rectangle.w;
    float ratio_hauteur  = tailleTexte.second * 1. / m_rectangle.h;
    float ratio = std::max(ratio_hauteur, ratio_largeur);
    int ancienneTaillePolice = TTF_FontHeight(m_policeTexte);
    int nouvelleTaillePolice = (ancienneTaillePolice / ratio);


    if(m_fonts.find(nouvelleTaillePolice) == m_fonts.end())
        m_fonts[nouvelleTaillePolice] = TTF_OpenFont(POLICE_COLLEGED.c_str(), nouvelleTaillePolice);
    m_policeTexte = m_fonts.at(nouvelleTaillePolice);

    m_texte = TTF_RenderText_Blended(m_policeTexte, m_texteStr.c_str(), m_couleurTexte);

    //tailleTexte = obtenirRectTexte();

}


void TexteSDL::positionner(std::pair<int, int> & coord){
    m_rectangle.x = coord.first;
    m_rectangle.y = coord.second;
}


std::pair<int, int> TexteSDL::obtenirRectTexte() const{
    int w,h;
    TTF_SizeText(m_policeTexte, m_texteStr.c_str(), &w, &h);
    return {w,h};
}


//!
//! \brief Mise à jour du contenu texte à afficher
//! \author fvain
//! \param nouveauTexte le nouveau texte à afficher
//! \version 0.1
//!
//! Mise à jour du texte
//!
void TexteSDL::mettreAJourTexte(std::string nouveau_texte){
    m_texteStr = nouveau_texte;
    if (m_texte != nullptr) SDL_FreeSurface(m_texte);
    m_texte = TTF_RenderText_Blended(m_policeTexte, nouveau_texte.c_str(), m_couleurTexte);
}


//!
//! \brief Mise à jour de la couleur du texte à afficher
//! \author fvain
//! \param SDL_Color la vouvelle couleur à afficher
//! \version 1.0
//!
//! Mise à jour de la couleur
//!
void TexteSDL::mettreAJourCouleur(SDL_Color nouvelle_couleur){
    m_couleurTexte = nouvelle_couleur;
    if (m_texte != nullptr) SDL_FreeSurface(m_texte);
    m_texte = TTF_RenderText_Blended(m_policeTexte, m_texteStr.c_str(), nouvelle_couleur);
}


std::string TexteSDL::obtenirTexteStr() const {
    return m_texteStr;
}


int TexteSDL::obtenirHauteurFont() const {
    if (m_texte != nullptr){
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
TexteSDL::~TexteSDL(){
    if (m_texte != nullptr) SDL_FreeSurface(m_texte);
}


//!
//! \brief Accesseur sur la police
//! \author rbourqui
//! \date 11/11/18
//! \version 0.1
//!
//! Retourne la police utilisée par le TexteSDL
//!

TTF_Font * TexteSDL::obtenirPolice(){
    return m_policeTexte;
}
