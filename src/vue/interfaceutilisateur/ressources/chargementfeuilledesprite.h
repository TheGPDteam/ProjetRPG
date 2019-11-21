#ifndef CHARGEMENTFEUILLEDESPRITES_H
#define CHARGEMENTFEUILLEDESPRITES_H

#include <SDL/SDL.h>
#include <iostream>
#include <map>

// METTRE AILLEUR
#include "modele/environnement/carte/tuile.h"


const std::string SPRITES_PRINCIPAUX = "SpritesPrincipaux";
const std::string SPRITE_BUS = "SpritesBus";

const std::map<int, SDL_Rect> TUILE2RECT = {};


class ChargementFeuilleDeSprites{
protected:
    static ChargementFeuilleDeSprites *m_instance;
    static bool m_objetConstruit;

    ChargementFeuilleDeSprites();

    SDL_Surface* optimisationChargementImage(const char *chemin_feuille_sprites);

    virtual ~ChargementFeuilleDeSprites();

public:
    static std::map<std::string, SDL_Surface*> m_imagesDeFeuilleDeSprites;
    static ChargementFeuilleDeSprites* instance();
    static void supprimerInstance();
};

#endif // CHARGEMENTFEUILLEDESPRITES_H
