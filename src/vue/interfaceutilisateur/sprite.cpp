#include "sprite.h"



//!
//! \brief Constructeur paramétré d'un sprite
//! \author pgutierrez
//! \date 11/11/16
//! @param cle_map_sprites clé de la map de la classe ChargementFeuilleDeSprite (chargementfeuilledesprite.h)
//! @param position_dans_fenetre position dans la fenetre d'affichage
//! @param position_dans_feuille_de_sprite position du sprite dans la feuille de sprite
//! \version 0.1
//!
//! Initialise le sprite en allant chercher son sprite correspondant dans la feuille de sprite
//!

Sprite::Sprite(const std::string cle_map_sprites, const SDL_Rect position_dans_fenetre, const SDL_Rect position_dans_feuille_de_sprite) :
    Affichable{position_dans_fenetre}, m_cleMapSprites(cle_map_sprites), m_coordDansLaFeuilleDeSprite(position_dans_feuille_de_sprite)
{

}


//!
//! \brief Change le sprite
//! \author pgutierrez
//! @param position_dans_feuille_de_sprite représente la position dans la feuille de sprite
//! \date 26/11/16
//! \version 1.0
//!
//! Change le sprite à partir de la feuille de sprite
//!

void Sprite::changementSprite(const SDL_Rect position_dans_feuille_de_sprite)
{
    m_coordDansLaFeuilleDeSprite = position_dans_feuille_de_sprite;
}


//!
//! \brief Affiche le sprite
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
//!
//! Affiche une partie de la feuille de sprite, partie correspondant au sprite voulu
//!

void Sprite::afficher(SDL_Surface* surface_affichage)
{
    ChargementFeuilleDeSprites * cfds =  ChargementFeuilleDeSprites::instance();
    auto it = cfds->m_imagesDeFeuilleDeSprites.find(m_cleMapSprites);

    if(it != cfds->m_imagesDeFeuilleDeSprites.end())
    {
        SDL_BlitSurface(it->second, &m_coordDansLaFeuilleDeSprite, surface_affichage, &m_rectangle);
    }
}


void Sprite::redimensionner(SDL_Rect rectangle){
    m_rectangle = rectangle;
}


//!
//! \brief Retourne la position du sprite
//! \author pgutierrez
//! \date 17/11/16
//! \version 1.0
//!
//! Retourne la position dans la fenêtre du sprite
//!

SDL_Rect Sprite::getCoordSprite()
{
    return m_rectangle;
}


//!
//! \brief Change les coordonnées du sprite
//! \author pgutierrez
//! @param x coordonnée x de la fenêtre
//! @param y coordonnée y de la fenêtre
//! \date 26/11/16
//! \version 1.0
//!
//! Permet de déplacer le sprite
//!

void Sprite::bougerSprite(int x, int y)
{
    m_rectangle.x = m_rectangle.x+(x*64);
    m_rectangle.y = m_rectangle.y+(y*64);
}

//!
//! \brief Destructeur d'un sprite
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
//!
//! Appelle le destructeur de la classe ChargementFeuilleDeSprite
//!

Sprite::~Sprite()
{

}
