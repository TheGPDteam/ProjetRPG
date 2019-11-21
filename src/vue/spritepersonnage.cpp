#include "spritepersonnage.h"

//! Constructeur de personnage
//!
//! \brief SpritePersonnage::SpritePersonnage
//! \param sprites
//!
SpritePersonnage::SpritePersonnage(std::vector<SpriteAnime *> sprites)
    :
      m_sprites_animes{sprites},
      m_direction_joueur{Direction::Aucune}
{}


//! Destructeur du personnage
//!
//!  \brief SpritePersonnage::~SpritePersonnage
//!
SpritePersonnage::~SpritePersonnage(){
    for (SpriteAnime* sprite_anime : m_sprites_animes){
        delete sprite_anime;
    }
}


//! Changer la position d'affichage du sprite du personnage
//!
//! \brief SpritePersonnage::changerPosition
//! \param x Nouvelle position x
//! \param y Nouvelle position y
//!
void SpritePersonnage::changerPosition(int x, int y){
    for (SpriteAnime* sprite_anime : m_sprites_animes){
        sprite_anime->changerPosition(x, y);
    }
}


//! Afficher le personnage
//!
//! \brief SpritePersonnage::afficher
//! \param surface Position d'affichage
//!
void SpritePersonnage::afficher(SDL_Surface *surface){
    m_sprites_animes.at(m_direction_joueur)->afficher(surface);
}


//! Appliquer une direction au personnage (vers où il regarde)
//!
//! \brief SpritePersonnage::deplacementJoueur
//! \param direction Direction qu'on donne au personnage
//!
void SpritePersonnage::deplacementJoueur(Direction direction){
    if (m_direction_joueur != direction){
        m_sprites_animes.at(m_direction_joueur)->reinitialiser();
        m_direction_joueur = direction;
    }
}


//! Obtenir les sprites du personnage
//!
//! \brief SpritePersonnage::obtenirSpritesJoueur
//! \return
//!
SpritePersonnage* SpritePersonnage::obtenirSpritesPersonnage(){
    std::vector<SpriteAnime*> sprites_animes = {
        // Haut
        new SpriteAnime({new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{0, 0, 64, 64}, SDL_Rect{2 * 64, 15 * 64, 64, 64}},
                         new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{0, 0, 64, 64}, SDL_Rect{3 * 64, 15 * 64, 64, 64}}},
        NB_ETAPES),

        // Bas
        new SpriteAnime({new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{0, 0, 64, 64}, SDL_Rect{2 * 64, 14 * 64, 64, 64}},
                         new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{0, 0, 64, 64}, SDL_Rect{3 * 64, 14 * 64, 64, 64}}}
        , NB_ETAPES),

        // Droite
        new SpriteAnime({new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{0, 0, 64, 64}, SDL_Rect{0 * 64, 15 * 64, 64, 64}},
                         new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{0, 0, 64, 64}, SDL_Rect{1 * 64, 15 * 64, 64, 64}}},
        NB_ETAPES),

        // Gauche
        new SpriteAnime({new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{0, 0, 64, 64}, SDL_Rect{0 * 64, 16 * 64, 64, 64}},
                         new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{0, 0, 64, 64}, SDL_Rect{1 * 64, 16 * 64, 64, 64}}},
        NB_ETAPES),

        // Immobile
        new SpriteAnime({new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{0, 0, 64, 64}, SDL_Rect{4 * 64, 14 * 64, 64, 64}}},
        NB_ETAPES)

    };

    return new SpritePersonnage(sprites_animes);
}
