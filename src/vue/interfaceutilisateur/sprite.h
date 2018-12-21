#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "chargementfeuilledesprite.h"
#include "affichable.h"

class Sprite : public Affichable
{
private:
    std::string m_cleMapSprites;
    SDL_Rect m_coordDansLaFeuilleDeSprite;

public:
    Sprite(const std::string cle_map_sprites, const SDL_Rect position_dans_fenetre, const SDL_Rect position_dans_feuille_de_sprite);
    Sprite() = default;
    virtual ~Sprite();

    void changementSprite(const SDL_Rect position_dans_feuille_de_sprite);
    void afficher(SDL_Surface *surface_affichage) override;
    void redimensionner(SDL_Rect rectangle);
    void bougerSprite(int x, int y);

    SDL_Rect getCoordSprite();

};

#endif // SPRITE_H
