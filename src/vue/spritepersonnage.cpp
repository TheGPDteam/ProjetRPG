#include "spritepersonnage.h"

SpritePersonnage::SpritePersonnage(std::vector<SpriteAnime *> sprites)
    :
      m_sprites_animes{sprites},
      m_direction_joueur{Direction::Sud}
{

}

void SpritePersonnage::afficher(SDL_Surface *surface)
{
        m_sprites_animes.at(m_direction_joueur)->afficher(surface);
}

void SpritePersonnage::deplacementJoueur(Direction direction)
{
    if (m_direction_joueur != direction)
    {
        m_sprites_animes.at(m_direction_joueur)->reinitialiser();
        m_direction_joueur = direction;
    }
}

SpritePersonnage* SpritePersonnage::obtenirSpritesJoueur()
{
    std::vector<SpriteAnime*> sprites_animes =
    {
        new SpriteAnime({new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256,256,64,64}},
                         new Sprite(SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256,256,64,64}),
                         new Sprite(SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256,256,64,64})
        }, 10),
        new SpriteAnime({new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256,256,64,64}},
                         new Sprite(SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256-64,256,64,64}),
                         new Sprite(SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256-128,256,64,64})
        }, 10),
        new SpriteAnime({new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256,256,64,64}},
                         new Sprite(SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256,256,64,64}),
                         new Sprite(SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256,256,64,64})
        }, 10),
        new SpriteAnime({new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256,256,64,64}},
                         new Sprite(SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256,256,64,64}),
                         new Sprite(SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256,256,64,64})
        }, 10)
    };
    return new SpritePersonnage(sprites_animes);
}

SpritePersonnage::~SpritePersonnage()
{
    for (SpriteAnime* sprite_anime : m_sprites_animes)
    {
        delete sprite_anime;
    }
}
