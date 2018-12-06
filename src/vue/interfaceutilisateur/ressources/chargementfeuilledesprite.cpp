#include "chargementfeuilledesprite.h"
#include <iostream>
using namespace  std;

std::map<std::string, SDL_Surface*> ChargementFeuilleDeSprites::m_imagesDeFeuilleDeSprites; // map servant à éviter les chargements multiple d'une même image ou feuille de sprite
bool ChargementFeuilleDeSprites::m_objetConstruit = false;
ChargementFeuilleDeSprites * ChargementFeuilleDeSprites::m_instance= nullptr;
//!
//! \brief Constructeur du système de chargement d'image
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
//!
//! Initialise un chargeur d'image en optimisant le format de cette dernière
//!

ChargementFeuilleDeSprites::ChargementFeuilleDeSprites()
{
}


//!
//! \brief Optimise une image
//! \return SDL_Surface*
//! \author pgutierrez
//! \date 11/11/16
//! @param chemin_feuille_sprites chemin allant jusqu'à la feuille de sprite
//! \version 0.2
//!
//! Optimise le format de l'image correspondant au chemin d'accès passé en paramétre
//!

SDL_Surface* ChargementFeuilleDeSprites::optimisationChargementImage(const char* chemin_feuille_sprites)
{
    m_objetConstruit = true;
    SDL_Surface* image;
    SDL_Surface* imageTemporaire = SDL_LoadBMP(chemin_feuille_sprites);

    if(imageTemporaire != nullptr)
    {
        image = SDL_DisplayFormat(imageTemporaire);
        SDL_FreeSurface(imageTemporaire);
    }
    else
    {
        std::cerr << SDL_GetError() << std::endl;
        exit(-1);
    }

    Uint32 colorkey = SDL_MapRGB( image->format, 128, 255, 255 );

    //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
    SDL_SetColorKey( image, SDL_SRCCOLORKEY, colorkey );

    return image;
}


//!
//! \brief Destructeur d'un chargeur d'image
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
//!
//! Détruit tout les SDL_Surface* (correspondant aux images chargées) de la map
//!

ChargementFeuilleDeSprites::~ChargementFeuilleDeSprites()
{
    if(!m_imagesDeFeuilleDeSprites.empty())
    {
        for( auto it = m_imagesDeFeuilleDeSprites.begin(); it != m_imagesDeFeuilleDeSprites.end(); ++it)
        {
            delete it->second;
        }

        m_imagesDeFeuilleDeSprites.clear();
    }
}

ChargementFeuilleDeSprites* ChargementFeuilleDeSprites::instance() {
    if(m_instance == nullptr)
        m_instance = new ChargementFeuilleDeSprites();
    if(!m_objetConstruit){
        m_imagesDeFeuilleDeSprites[SPRITES_PRINCIPAUX] = m_instance->optimisationChargementImage("../rsc/sprites/Sprites.bmp");
    }
   return m_instance;
}


void ChargementFeuilleDeSprites::supprimerInstance(){
    if(m_instance != nullptr)
        delete m_instance;
}
