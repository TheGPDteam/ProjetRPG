#include "bouton.h"
#include "constantesbouton.h"


std::string Bouton::m_cleMapSprites = SPRITES_PRINCIPAUX; //Ceci est la clé permettant de trouver la bonne feuille de sprite pour les boutons


//!
//! \brief Constructeur paramétré d'un bouton
//! \author pgutierrez
//! \date 11/11/16
//! @param type_bouton type du bouton
//! @param texte texte du bouton
//! @param couleur_texte couleur du texte du bouton
//! @param chemin_police police du texte du bouton
//! @param taille_police la taille de la police
//! @param coord_bouton coordonnées du bouton
//! @param taille_bouton taille du bouton
//! \version 0.2
//!
//! Initialise l'image et le texte qu'aura le bouton
//!

Bouton::Bouton(const TypeBouton type_bouton, const bool bouton_cliquable, std::string texte, const std::string chemin_police, const int taille_police,
               const std::pair<int, int> coord_bouton, const std::pair<int, int> taille_bouton) : m_typeDeBouton(type_bouton), m_boutonCliquable(bouton_cliquable)

{
    initialisationAffichageBouton(coord_bouton);

    if(m_boutonCliquable)
    {
        m_texteBouton = new TexteSDL(texte, COULEUR_BOUTON_CLIQUABLE, chemin_police, taille_police, coord_bouton, taille_bouton);
    }
    else
    {
        m_texteBouton = new TexteSDL(texte, COULEUR_BOUTON_NON_CLIQUABLE, chemin_police, taille_police, coord_bouton, taille_bouton);
    }
}



//!
//! \brief Indique si l'événement se passe sur la bouton
//! \return bool
//! \author pgutierrez
//! \date 18/11/16
//! @param coord_x_souris coordonnées de la souris en X
//! @param coord_y_souris coordonnées de la souris en Y
//! \version 1.0
//!
//! Retourne vrai si l'événement se passe sur le bouton, retourne faux sinon
//!

bool Bouton::evenementSurBouton(std::pair<int, int> coord_souris)
{
    if(coord_souris.first > m_spriteBouton->getCoordSprite().x && coord_souris.first < m_spriteBouton->getCoordSprite().x + m_spriteBouton->getCoordSprite().w &&
            coord_souris.second > m_spriteBouton->getCoordSprite().y && coord_souris.second < m_spriteBouton->getCoordSprite().y + m_spriteBouton->getCoordSprite().h)
    {
        return true;
    }

    return false;
}


//!
//! \brief Affiche un bouton
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
//!
//! Elle affiche le sprite et le texte du bouton
//!

void Bouton::afficherBouton(SDL_Surface* surface_affichage)
{
    m_spriteBouton->afficherSprite(surface_affichage);
    m_texteBouton->afficherTexte(surface_affichage);
}


//!
//! \brief Retourne le sprite du bouton
//! \return Sprite
//! \author pgutierrez
//! \date 26/11/16
//! \version 1.0
//!

Sprite* Bouton::obtenirSpriteBouton()
{
    return m_spriteBouton;
}


//!
//! \brief Retourne le type du bouton
//! \return TypeBouton
//! \author pgutierrez
//! \date 26/11/16
//! \version 1.0
//!

TypeBouton Bouton::obtenirTypeBouton()
{
    return m_typeDeBouton;
}


//!
//! \brief Retourne si le bouton est cliquable
//! \return bool
//! \author pgutierrez
//! \date 26/11/16
//! \version 1.0
//!

bool Bouton::obtenirBoutonCliquable() {
    return m_boutonCliquable;
}

//!
//! \brief Initialise le sprite du bouton
//! \author pgutierrez
//! \date 11/11/16
//! @param coord_bouton coordonnées du bouton
//! \version 0.2
//!
//! Initialise le sprite du bouton en fonction du type du bouton
//!

void Bouton::initialisationAffichageBouton(const std::pair<int, int> coord_bouton)
{
    SDL_Rect positionFenetre;
    SDL_Rect positionFeuilleDeSprite;

    switch(m_typeDeBouton)
    {
    case Normal:
        positionFenetre = initialisationRectangle(coord_bouton.first, coord_bouton.second, 0, 0);
        positionFeuilleDeSprite = initialisationRectangle(COORD_X_BOUTON_NORMAL, COORD_Y_BOUTON_NORMAL, WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

        m_spriteBouton = new Sprite(SPRITES_PRINCIPAUX, positionFenetre, positionFeuilleDeSprite);
        break;
    case Onglet:

        break;
    case SelecteurActif:

        break;
    case SelecteurInactif:

        break;
    }
}


//!
//! \brief Initialise un simple SDL_Rect
//! \return SDL_Rect
//! \author pgutierrez
//! \date 11/11/16
//! @param x coordonnée X du rectangle
//! @param y coordonnée Y du rectangle
//! @param width couleur du texte du bouton
//! @param height police du texte du bouton
//! \version 0.2
//!
//! Initialise un rectangle paramétrable
//!

SDL_Rect Bouton::initialisationRectangle(const int x, const int y, const int width, const int height)
{
    SDL_Rect rectangleTemporaire;
    rectangleTemporaire.x = x;
    rectangleTemporaire.y = y;
    rectangleTemporaire.w = width;
    rectangleTemporaire.h = height;

    return rectangleTemporaire;
}



//!
//! \brief Destructeur d'un bouton
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
//!
//! Détruit l'image et le texte d'un bouton si ils ont été initialisé
//!

Bouton::~Bouton()
{
    if(m_spriteBouton != nullptr)
    {
        delete m_spriteBouton;
    }

    if(m_texteBouton != nullptr)
    {
        delete m_texteBouton;
    }
}
