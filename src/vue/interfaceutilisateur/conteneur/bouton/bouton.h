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

    SDL_Rect zone() const override { return m_spriteBouton->obtenirCoordonneesSprite();}

public:

    Bouton(const std::string texte,
           SDL_Rect obtenirRectangle,
           Controleur * controleur,
           void *action,
           const bool bouton_cliquable = true,
           //const std::pair<float, float> coef_coord_texte = std::make_pair(0.5,0.5),
           const std::string police = "Defaut"
            );

    ~Bouton() override;

    //!
    //! \brief afficher hérité de Affichable
    //!
    void afficher(SDL_Surface* surface) override;

    void redimensionner(SDL_Rect rect) override;

    //Accés variables
    std::string obtenirTexte();

    //    bool estCliquable();

    void definirCliquable(bool actif) override;

    void changerSpriteBouton(Sprite *spriteBouton);

    Sprite* obtenirSpriteBouton();

    void clique() override {}

};

#endif // BOUTON_H
