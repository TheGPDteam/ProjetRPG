#ifndef BOUTON_H
#define BOUTON_H

#include "../../textesdl.h"
#include "../../sprite.h"
#include "vue/affichable.h"
#include "../../cliquable.h"

#include "../../zonetexte.h"
#include <iostream>

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

    std::string obtenirTexte();
    void changerTexte(std::string texte);

    void definirCliquable(bool actif) override;

    void changerSpriteBouton(Sprite *spriteBouton);

    Sprite* obtenirSpriteBouton();

    void clique() override {}

    std::string serialiser() const {
        SDL_Rect rect = zone();
        std::string res =  std::to_string(rect.x) + " " + std::to_string(rect.y) + " " + std::to_string(rect.w) + " " + std::to_string(rect.h) ;
        return res;
    }
};

#endif // BOUTON_H
