#ifndef SPRITEPERSONNAGE_H
#define SPRITEPERSONNAGE_H

#include "direction.h"
#include "spriteanime.h"
#include "vector"

const int NB_ETAPES = 8;

class SpritePersonnage
{
private:
    Direction m_direction_joueur;
    std::vector<SpriteAnime*> m_sprites_animes;
public:
    SpritePersonnage() = delete;
    SpritePersonnage(std::vector<SpriteAnime*> sprites);

    void afficher(SDL_Surface* surface);
    void deplacementJoueur(Direction direction);
    static SpritePersonnage* obtenirSpritesPersonnage();
    void changerPosition(int x, int y);
    ~SpritePersonnage();
};

#endif // SPRITEPERSONNAGE_H
