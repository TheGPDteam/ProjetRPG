#ifndef BOUTON_H
#define BOUTON_H

#include "../../textesdl.h"
#include "../../sprite.h"


class Bouton : public Affichable, public Cliquable
{
private:

    ZoneTexte* m_texteBouton;

    Sprite* m_spriteBouton;


public:

    //!
    //! \author cerutti & pin
    //! \date 22/10/18
    //! \version 0.1
    //!
    //! @brief Crée un bouton.
    //! @param texte le texte à afficher.
    //! @param rectangle, la position x, y, longueur, hauteur.
    //! @param sprite, l'image de fond.
    //! @param action, la fonction à appeler.
    //! @param coef_coord_texte, les coefficients d'ancrage du texte relativement au bouton.
    //! 0,0 en haut à gauche jusqu'à 1,1.
    //! @param bouton_cliquable, true si il est cliquable.
    //!
    Bouton( const std::string texte,
            const SDL_Rect rectangle,
            const Sprite* sprite,
            void (*action)(),
            const std::pair<float, float> coef_coord_texte = std::make_pair(0.5,0.5),
            const bool bouton_cliquable = true
            );


    ~Bouton();

    void afficher();

    //Accés variables

    bool estCliquable();

    void devenirCliquable( bool peutCliquer );

    void changerSpriteBouton(Sprite *spriteBouton);

    Sprite* obtenirSpriteBouton();

};

#endif // BOUTON_H
