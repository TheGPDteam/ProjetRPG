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


    Bouton( const std::string texte,
            const SDL_Rect rectangle,
            const Sprite* sprite,
            void (*action)(),
            const std::pair<float, float> coef_coord_texte = std::make_pair(0.5,0.5),
            const bool bouton_cliquable = true,
            const std::string police = "Defaut"
            );


    ~Bouton();

    /**
     * @brief afficher hérité de Affichable
     */
    void afficher(SDL_Surface* surface_affichage);

    //Accés variables

    bool estCliquable();

    void definirCliquable(bool peut_cliquer );

    void changerSpriteBouton(Sprite *spriteBouton);

    Sprite* obtenirSpriteBouton();

};

#endif // BOUTON_H
