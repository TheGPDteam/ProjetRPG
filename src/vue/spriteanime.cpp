#include "spriteanime.h"

SpriteAnime::SpriteAnime(std::vector<Sprite*> sprites, int temps_affichage)
    :
      m_sprites{sprites},
      m_sprite_courant{0},
      m_temps_affichage{temps_affichage},
      m_temps_sprite_courant{0}
{
}

void SpriteAnime::afficher(SDL_Surface* surface){
    if (++m_temps_sprite_courant >= m_temps_affichage){
        m_temps_sprite_courant = 0;
        m_sprite_courant = ++m_sprite_courant % m_sprites.size();
    } else m_temps_sprite_courant++;

    m_sprites.at(m_sprite_courant)->afficher(surface);
}

void SpriteAnime::reinitialiser(){
    m_temps_sprite_courant = 0;
    m_sprite_courant = 0;
}

SpriteAnime::~SpriteAnime(){
    for  (Sprite* sprite : m_sprites){
        delete sprite;
    }
}
