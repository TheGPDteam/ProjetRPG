#include "bouton.h"
#include "constantesbouton.h"


//!
//! \brief Constructeur paramétré d'un bouton
//! \author pgutierrez
//! \date 11/11/16
//! \param type_bouton type du bouton
//! \param texte texte du bouton
//! \param couleur_texte couleur du texte du bouton
//! \param chemin_police police du texte du bouton
//! \param taille_police la taille de la police
//! \param coord_bouton coordonnées du bouton
//! \param taille_bouton taille du bouton
//! \version 0.2
//!
//! Initialise l'image et le texte qu'aura le bouton
//!

Bouton::Bouton( texte,
                rectangle,
                sprite,
                coef_coord_texte,
                bouton_cliquable)
    : m_texteBouton()
{
    if(m_boutonCliquable)
    {
        m_texteBouton = new TexteSDL(texte, COULEUR_BOUTON_CLIQUABLE, chemin_police, taille_police, coord_texte);
    }
    else
    {
        m_texteBouton = new TexteSDL(texte, COULEUR_BOUTON_NON_CLIQUABLE, chemin_police, taille_police, coord_texte);
    }
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


//!
//! \brief Affiche un bouton
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
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
//! \brief Affecte le sprite du bouton
//! \param spriteBouton
//!

void Bouton::setSpriteBouton(Sprite *spriteBouton)
{
    m_spriteBouton = spriteBouton;
}



//!
//! \brief Met l'attribut cliquable au paramêtre
//! \author mleothaud
//! \date 11/11/16
//! \version 1.0
//!

void Bouton::devenirCliquable()
{
    m_boutonCliquable = true;
}
