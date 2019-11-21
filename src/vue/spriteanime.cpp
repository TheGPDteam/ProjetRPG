#include "spriteanime.h"

SpriteAnime::SpriteAnime(std::vector<Sprite*> sprites, int temps_affichage)
    :
      m_sprites{sprites},
      m_sprite_courant{0},
      m_temps_affichage{temps_affichage},
      m_temps_sprite_courant{0}
{
}


//! Destructeur Sprite anime
//!
//! \brief SpriteAnime::~SpriteAnime
//!
SpriteAnime::~SpriteAnime(){
    for  (Sprite* sprite : m_sprites){
        delete sprite;
    }
}


//! Afficher le sprite anime
//!
//! \brief SpriteAnime::afficher
//! \param surface
//!
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


//! Changer la position d'affichage du sprite anime
//!
//! \brief SpriteAnime::changerPosition
//! \param x Nouvelle position x (à gauche du rectangle)
//! \param y Nouvelle position y (en haut du rectangle)
//!
void SpriteAnime::changerPosition(int x, int y){
    for  (Sprite* sprite : m_sprites){
        sprite->changerPosition(x, y);
    }
}
