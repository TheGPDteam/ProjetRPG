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

Bouton::Bouton( const std::string texte,
                const SDL_Rect rectangle,
                const Sprite* sprite,
                void (*action)(),
                const std::pair<float, float> coef_coord_texte = std::make_pair(0.5,0.5),
                const bool bouton_cliquable = true,
                const std::string police = "Default"
        )
    :
      Affichable(rectangle),
      Cliquable(action, bouton_cliquable),
      m_texteBouton(new ZoneTexte(texte, rectangle, police)),
      m_spriteBouton(sprite)

{
    if(m_boutonCliquable)
    {
        //m_texteBouton.setColor(COULEUR_BOUTON_CLIQUABLE);
    }
    else
    {
        //ANCIEN
        //m_texteBouton = new TexteSDL(texte, COULEUR_BOUTON_NON_CLIQUABLE, chemin_police, taille_police, coord_texte);
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

void Bouton::afficher(SDL_Surface* surface_affichage)
{
    m_spriteBouton->afficher(surface_affichage);
    m_texteBouton->afficher(surface_affichage);
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


///A CHANGER AVEC CLIQUABLE
//!
//! \brief Retourne si le bouton est cliquable
//! \return bool
//! \author pgutierrez
//! \date 26/11/16
//! \version 1.1
//!

bool Bouton::obtenirBoutonCliquable() {
    return true;
}

//!
//! \brief Met l'attribut cliquable a can_click
//! \author cerutti & lacoste
//! \date 25/10/18
//! \param peut_cliquer,
//! \version 1.1
//!
void Bouton::definirCliquable(bool peut_cliquer)
{
    /*
    if(peut_cliquer)
    {
        //m_texteBouton.definirCouleur(COULEUR_BOUTON_CLIQUABLE);
    }
    else
    {
        //m_texteBouton.definirCouleur(COULEUR_BOUTON_NONCLIQUABLE);
    }
    //m_boutonCliquable = peut_cliquer;
}
