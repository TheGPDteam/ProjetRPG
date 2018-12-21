#ifndef BOUTON_H
#define BOUTON_H

#include "../../textesdl.h"
#include "../../sprite.h"
#include "vue/affichable.h"
#include "../../cliquable.h"

#include "../../zonetexte.h"


class Bouton : public Affichable, public Cliquable
{
private:

    ZoneTexte* m_texteBouton;
    //TexteSDL * m_texte;
    Sprite* m_spriteBouton;

    SDL_Rect  zone() const { return m_spriteBouton->getCoordSprite();}

public:

    Bouton(const std::string texte,
            SDL_Rect rectangle,
            Controleur * controleur,
            void *action,
            const bool bouton_cliquable = true,
            //const std::pair<float, float> coef_coord_texte = std::make_pair(0.5,0.5),
            const std::string police = "Defaut"
            );

    ~Bouton();

    //!
    //! \brief afficher hérité de Affichable
    //!
    void afficher(SDL_Surface* surface);

    void redimensionner(SDL_Rect rect) override{}

    //Accés variables

    bool estCliquable();

    void definirCliquable(bool peutCliquer );

    void changerSpriteBouton(Sprite *spriteBouton);

    Sprite* obtenirSpriteBouton();

    void clique() override {}

};

#endif // BOUTON_H
