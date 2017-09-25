#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "chargementfeuilledesprite.h"

class Sprite
{
private:
    std::string m_cleMapSprites;
    SDL_Rect m_coordDansLaFenetre;
    SDL_Rect m_coordDansLaFeuilleDeSprite;

public:
    Sprite(const std::string cle_map_sprites, const SDL_Rect position_dans_fenetre, const SDL_Rect position_dans_feuille_de_sprite);

    void changementSprite(const SDL_Rect position_dans_feuille_de_sprite);
    void afficherSprite(SDL_Surface *surface_affichage);
    void bougerSprite(int x, int y);

    SDL_Rect getCoordSprite();

    ~Sprite();
};

#endif // SPRITE_H
