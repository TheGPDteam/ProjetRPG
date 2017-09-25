#ifndef CHARGEMENTFEUILLEDESPRITES_H
#define CHARGEMENTFEUILLEDESPRITES_H

#include <SDL/SDL.h>
#include <iostream>
#include <map>

const std::string SPRITES_PRINCIPAUX = "SpritesPrincipaux";

class ChargementFeuilleDeSprites
{
protected:
    static ChargementFeuilleDeSprites *m_instance;
    static bool m_objetConstruit;

    ChargementFeuilleDeSprites();

    SDL_Surface* optimisationChargementImage(const char *chemin_feuille_sprites);


    virtual ~ChargementFeuilleDeSprites();

public:
    static std::map<std::string, SDL_Surface*> m_imagesDeFeuilleDeSprites;

    static ChargementFeuilleDeSprites* instance();

};

#endif // CHARGEMENTFEUILLEDESPRITES_H
