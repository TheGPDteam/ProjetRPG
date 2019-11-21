#ifndef SPRITEANIME_H
#define SPRITEANIME_H

#include "sprite.h"
#include <vector>

class SpriteAnime
{
private:
    std::vector<Sprite*> m_sprites;
    int m_sprite_courant;
    int m_temps_affichage;
    int m_temps_sprite_courant;
public:
    SpriteAnime(std::vector<Sprite *> sprites, int temps_affichable);
    void afficher(SDL_Surface* surface);
    void reinitialiser();
    void changerPosition(int x, int y);
    ~SpriteAnime();
};

#endif // SPRITEANIME_H
