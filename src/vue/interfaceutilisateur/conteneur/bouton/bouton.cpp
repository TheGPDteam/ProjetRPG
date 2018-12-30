#include "bouton.h"
#include "constantesbouton.h"
#include "../../../outilsvue.h"


//std::string Bouton::m_cleMapSprites = SPRITES_PRINCIPAUX; //Ceci est la clé permettant de trouver la bonne feuille de sprite pour les boutons

const SDL_Rect POSITION_FEUILLE_SPRITE = initialiserRectangle(COORD_X_BOUTON_NORMAL, COORD_Y_BOUTON_NORMAL, WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

//!
//! \brief Constructeur parametre d'un bouton
//! \author cerutti & pin
//! \date 25/10/18
//! @param type_bouton type du bouton
//! @param texte texte du bouton
//! @param couleur_texte couleur du texte du bouton
//! @param chemin_police police du texte du bouton
//! @param taille_police la taille de la police
//! @param coord_bouton coordonnées du bouton
//! @param taille_bouton taille du bouton
//! \version 0.2
//!
//! Initialise l'image et le texte qu'aura le bouton, ainsi
//! que l'action pour les événements de notre boutons.
//!
Bouton::Bouton(const std::string texte,
               SDL_Rect rectangle,
               Controleur *controleur,
               void *action,
               const bool bouton_cliquable,
               //const std::pair<float, float> coef_coord_texte,
               const std::string police
               )
    :
      Affichable(rectangle),
      Cliquable(controleur, /*action,*/ bouton_cliquable),
      m_texteBouton(new ZoneTexte(police, 18, rectangle, texte, (bouton_cliquable ? COULEUR_BOUTON_CLIQUABLE : COULEUR_BOUTON_NON_CLIQUABLE))),
      m_spriteBouton(new Sprite(SPRITES_PRINCIPAUX, rectangle, POSITION_FEUILLE_SPRITE))
{}

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

//!
//! \brief Affiche un bouton
//! \author cerutti
//! \date 25/10/18
//! \version 1.0
//!
//! Elle affiche le sprite et le texte du bouton
//!


void Bouton::afficher(SDL_Surface* surface)
{
    m_spriteBouton->afficher(surface);
    m_texteBouton->afficher(surface);
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


void Bouton::definirCliquable(bool actif){
    Cliquable::definirCliquable(actif);
    m_texteBouton->mettreAJourCouleur((actif ? COULEUR_BOUTON_CLIQUABLE : COULEUR_BOUTON_NON_CLIQUABLE));
}

void Bouton::redimensionner(SDL_Rect m_rectangle){
    this->m_rectangle = m_rectangle;
}

std::string Bouton::obtenirTexte(){
    return m_texteBouton->obtenirTexte();
}
