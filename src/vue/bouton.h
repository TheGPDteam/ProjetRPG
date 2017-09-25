#ifndef BOUTON_H
#define BOUTON_H

#include "textesdl.h"
#include "sprite.h"
#include "typebouton.h"


class Bouton
{
private:
    static std::string m_cleMapSprites;

    TypeBouton m_typeDeBouton;
    TexteSDL* m_texteBouton;
    Sprite* m_spriteBouton;

    bool m_boutonCliquable;

    void initialisationAffichageBouton(const std::pair<int, int> coord_bouton);
    SDL_Rect initialisationRectangle(const int x, const int y, const int width, const int height);

public:
    Bouton(const TypeBouton type_bouton, const bool bouton_cliquable, const std::string texte, const std::string chemin_police, const int taille_police,
            const std::pair<int, int> coord_bouton, const std::pair<int, int> taille_bouton);

    bool evenementSurBouton(std::pair<int, int> coord_souris);
    void afficherBouton(SDL_Surface *surface_affichage);

    Sprite* obtenirSpriteBouton();
    TypeBouton obtenirTypeBouton();
    bool obtenirBoutonCliquable();

    ~Bouton();
};

#endif // BOUTON_H
