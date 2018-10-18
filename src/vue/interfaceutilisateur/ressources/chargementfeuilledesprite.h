#ifndef CHARGEMENTFEUILLEDESPRITES_H
#define CHARGEMENTFEUILLEDESPRITES_H

#include <SDL/SDL.h>
#include <iostream>
#include <map>

// METTRE AILLEUR
#include "modele/environnement/carte/tuile.h"


const std::string SPRITES_PRINCIPAUX = "SpritesPrincipaux";
const std::map<int, SDL_Rect> EAU = {
    {Tuile::hacher(TypeTuile::AucunType,TypeJonction::AucuneJonction), SDL_Rect{832,0,64,64} }
};

const std::map<int, SDL_Rect> ARBRE = {
    {Tuile::hacher(TypeTuile::AucunType, TypeJonction::AucuneJonction), SDL_Rect{256,64,64,64}}
};
const std::map<int, SDL_Rect> SABLE = {
    {Tuile::hacher(TypeTuile::AucunType, TypeJonction::AucuneJonction), SDL_Rect{704,0,64,64} },
    /* EAU                  0 */
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::BasDroiteEntrant), SDL_Rect{704,192,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::HautDroiteEntrant), SDL_Rect{704,256,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::Bas), SDL_Rect{704,320,64,64} },

    {Tuile::hacher(TypeTuile::Eau, TypeJonction::BasGaucheEntrant), SDL_Rect{768,192,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::HautGaucheEntrant), SDL_Rect{768,256,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::Haut), SDL_Rect{768,320,64,64} },

    {Tuile::hacher(TypeTuile::Eau, TypeJonction::HautGaucheSortant), SDL_Rect{832,192,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::BasGaucheSortant), SDL_Rect{832,256,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::Gauche), SDL_Rect{832,320,64,64} },

    {Tuile::hacher(TypeTuile::Eau, TypeJonction::HautDroiteSortant), SDL_Rect{896,192,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::BasDroiteSortant), SDL_Rect{896,256,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::Droite), SDL_Rect{896,320,64,64} },
    /* TERRE                4*/
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::HautGaucheSortant), SDL_Rect{960,192,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::BasGaucheSortant), SDL_Rect{960,256,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::Bas), SDL_Rect{960,320,64,64} },

    {Tuile::hacher(TypeTuile::Terre, TypeJonction::HautDroiteSortant), SDL_Rect{1024,192,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::BasDroiteSortant), SDL_Rect{1024,256,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::Haut), SDL_Rect{1024,320,64,64} },

    {Tuile::hacher(TypeTuile::Terre, TypeJonction::BasDroiteEntrant), SDL_Rect{1088,192,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::HautDroiteEntrant), SDL_Rect{1088,256,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::Gauche), SDL_Rect{1088,320,64,64} },

    {Tuile::hacher(TypeTuile::Terre, TypeJonction::BasGaucheEntrant), SDL_Rect{1152,192,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::HautGaucheEntrant), SDL_Rect{1152,256,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::Droite), SDL_Rect{1152,320,64,64} },

    /* BETON                3*/
    {Tuile::hacher(TypeTuile::Beton, TypeJonction::HautGaucheSortant), SDL_Rect{1216,192,64,64} },
    {Tuile::hacher(TypeTuile::Beton, TypeJonction::BasGaucheSortant), SDL_Rect{1216,256,64,64} },
    {Tuile::hacher(TypeTuile::Beton, TypeJonction::Bas), SDL_Rect{1216,320,64,64} },

    {Tuile::hacher(TypeTuile::Beton, TypeJonction::HautDroiteSortant), SDL_Rect{1280,192,64,64} },
    {Tuile::hacher(TypeTuile::Beton, TypeJonction::BasDroiteSortant), SDL_Rect{1280,256,64,64} },
    {Tuile::hacher(TypeTuile::Beton, TypeJonction::Haut), SDL_Rect{1280,320,64,64} },

    {Tuile::hacher(TypeTuile::Beton, TypeJonction::BasDroiteEntrant), SDL_Rect{1344,192,64,64} },
    {Tuile::hacher(TypeTuile::Beton, TypeJonction::HautDroiteEntrant), SDL_Rect{1344,256,64,64} },
    {Tuile::hacher(TypeTuile::Beton, TypeJonction::Gauche), SDL_Rect{1344,320,64,64} },

    {Tuile::hacher(TypeTuile::Beton, TypeJonction::BasGaucheEntrant), SDL_Rect{1408,192,64,64} },
    {Tuile::hacher(TypeTuile::Beton, TypeJonction::HautGaucheEntrant), SDL_Rect{1408,256,64,64} },
    {Tuile::hacher(TypeTuile::Beton, TypeJonction::Droite), SDL_Rect{1408,320,64,64} },

    /* ARBRE (HERBE)        5*/
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautGaucheSortant), SDL_Rect{1728,192,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasGaucheSortant), SDL_Rect{1728,256,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Bas), SDL_Rect{1728,320,64,64} },

    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautDroiteSortant), SDL_Rect{1792,192,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasDroiteSortant), SDL_Rect{1792,256,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Haut), SDL_Rect{1792,320,64,64} },

    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasDroiteEntrant), SDL_Rect{1856,192,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautDroiteEntrant), SDL_Rect{1856,256,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Gauche), SDL_Rect{1856,320,64,64} },

    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasGaucheEntrant), SDL_Rect{1920,192,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautGaucheEntrant), SDL_Rect{1920,256,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Droite), SDL_Rect{1920,320,64,64} }
};

const std::map<int, SDL_Rect> HERBE = {
    {Tuile::hacher(TypeTuile::AucunType, TypeJonction::AucuneJonction), SDL_Rect{768,0,64,64} },
    /* EAU                      0*/
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::BasDroiteEntrant), SDL_Rect{960,0,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::HautDroiteEntrant), SDL_Rect{960,64,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::Gauche), SDL_Rect{960,128,64,64} },

    {Tuile::hacher(TypeTuile::Eau, TypeJonction::BasGaucheEntrant), SDL_Rect{1024,0,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::HautGaucheEntrant), SDL_Rect{1024,64,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::Droite), SDL_Rect{1024,128,64,64} },

    {Tuile::hacher(TypeTuile::Eau, TypeJonction::HautGaucheSortant), SDL_Rect{1088,0,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::BasGaucheSortant), SDL_Rect{1088,64,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::Bas), SDL_Rect{1088,128,64,64} },

    {Tuile::hacher(TypeTuile::Eau, TypeJonction::HautDroiteSortant), SDL_Rect{1152,0,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::BasDroiteSortant), SDL_Rect{1152,64,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::Haut), SDL_Rect{1152,128,64,64} },

    /* ARBRE (pas de jonction)  5*/

    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautGaucheSortant), SDL_Rect{768,0,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasGaucheSortant), SDL_Rect{768,0,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Bas), SDL_Rect{768,0,64,64} },

    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautDroiteSortant), SDL_Rect{768,0,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasDroiteSortant), SDL_Rect{768,0,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Haut), SDL_Rect{768,0,64,64} },

    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasDroiteEntrant), SDL_Rect{768,0,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautDroiteEntrant), SDL_Rect{768,0,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Gauche), SDL_Rect{768,0,64,64} },

    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasGaucheEntrant), SDL_Rect{768,0,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautGaucheEntrant), SDL_Rect{768,0,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Droite), SDL_Rect{768,0,64,64} },


    /* SABLE                1*/
    {Tuile::hacher(TypeTuile::Sable, TypeJonction::BasDroiteEntrant), SDL_Rect{1728,192,64,64} },
    {Tuile::hacher(TypeTuile::Sable, TypeJonction::HautDroiteEntrant), SDL_Rect{1728,256,64,64} },
    {Tuile::hacher(TypeTuile::Sable, TypeJonction::Haut), SDL_Rect{1728,320,64,64} },

    {Tuile::hacher(TypeTuile::Sable, TypeJonction::BasGaucheEntrant), SDL_Rect{1792,192,64,64} },
    {Tuile::hacher(TypeTuile::Sable, TypeJonction::HautGaucheEntrant), SDL_Rect{1792,256,64,64} },
    {Tuile::hacher(TypeTuile::Sable, TypeJonction::Bas), SDL_Rect{1792,320,64,64} },

    {Tuile::hacher(TypeTuile::Sable, TypeJonction::HautGaucheSortant), SDL_Rect{1856,192,64,64} },
    {Tuile::hacher(TypeTuile::Sable, TypeJonction::BasGaucheSortant), SDL_Rect{1856,256,64,64} },
    {Tuile::hacher(TypeTuile::Sable, TypeJonction::Droite), SDL_Rect{1856,320,64,64} },

    {Tuile::hacher(TypeTuile::Sable, TypeJonction::HautDroiteSortant), SDL_Rect{1920,192,64,64} },
    {Tuile::hacher(TypeTuile::Sable, TypeJonction::BasDroiteSortant), SDL_Rect{1920,256,64,64} },
    {Tuile::hacher(TypeTuile::Sable, TypeJonction::Gauche), SDL_Rect{1920,320,64,64} }
};
const std::map<int, SDL_Rect> BETON = {
    {Tuile::hacher(TypeTuile::AucunType, TypeJonction::AucuneJonction), SDL_Rect{896,0,64,64} },
    /* ARBRE (HERBE)        5*/
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasDroiteEntrant), SDL_Rect{1472,192,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautDroiteEntrant), SDL_Rect{1472,256,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Haut), SDL_Rect{1472,320,64,64} },

    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasGaucheEntrant), SDL_Rect{1536,192,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautGaucheEntrant), SDL_Rect{1536,256,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Bas), SDL_Rect{1536,320,64,64} },

    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautGaucheSortant), SDL_Rect{1600,192,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasGaucheSortant), SDL_Rect{1600,256,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Droite), SDL_Rect{1600,320,64,64} },

    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautDroiteSortant), SDL_Rect{1728,192,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasDroiteSortant), SDL_Rect{1728,256,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Gauche), SDL_Rect{1728,320,64,64} },

    /* HERBE                2*/
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::BasDroiteEntrant), SDL_Rect{1472,192,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::HautDroiteEntrant), SDL_Rect{1472,256,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::Haut), SDL_Rect{1472,320,64,64} },

    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::BasGaucheEntrant), SDL_Rect{1536,192,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::HautGaucheEntrant), SDL_Rect{1536,256,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::Bas), SDL_Rect{1536,320,64,64} },

    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::HautGaucheSortant), SDL_Rect{1600,192,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::BasGaucheSortant), SDL_Rect{1600,256,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::Droite), SDL_Rect{1600,320,64,64} },

    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::HautDroiteSortant), SDL_Rect{1728,192,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::BasDroiteSortant), SDL_Rect{1728,256,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::Gauche), SDL_Rect{1728,320,64,64} },

    /* TERRE                4*/
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::BasDroiteEntrant), SDL_Rect{1472,0,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::HautDroiteEntrant), SDL_Rect{1472,64,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::Haut), SDL_Rect{1472,128,64,64} },

    {Tuile::hacher(TypeTuile::Terre, TypeJonction::BasGaucheEntrant), SDL_Rect{1536,0,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::HautGaucheEntrant), SDL_Rect{1536,64,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::Bas), SDL_Rect{1536,128,64,64} },

    {Tuile::hacher(TypeTuile::Terre, TypeJonction::HautGaucheSortant), SDL_Rect{1600,0,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::BasGaucheSortant), SDL_Rect{1600,64,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::Droite), SDL_Rect{1600,128,64,64} },

    {Tuile::hacher(TypeTuile::Terre, TypeJonction::HautDroiteSortant), SDL_Rect{1664,0,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::BasDroiteSortant), SDL_Rect{1664,64,64,64} },
    {Tuile::hacher(TypeTuile::Terre, TypeJonction::Gauche), SDL_Rect{1664,128,64,64} }
};
const std::map<int, SDL_Rect> TERRE = {
    {Tuile::hacher(TypeTuile::AucunType, TypeJonction::AucuneJonction), SDL_Rect{704,64,64,64} },
    /* EAU                      0*/
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::BasDroiteEntrant), SDL_Rect{1216,0,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::HautDroiteEntrant), SDL_Rect{1216,64,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::Gauche), SDL_Rect{1216,128,64,64} },

    {Tuile::hacher(TypeTuile::Eau, TypeJonction::BasGaucheEntrant), SDL_Rect{1280,0,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::HautGaucheEntrant), SDL_Rect{1280,64,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::Droite), SDL_Rect{1280,128,64,64} },

    {Tuile::hacher(TypeTuile::Eau, TypeJonction::HautGaucheSortant), SDL_Rect{1344,0,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::BasGaucheSortant), SDL_Rect{1344,64,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::Bas), SDL_Rect{1344,128,64,64} },

    {Tuile::hacher(TypeTuile::Eau, TypeJonction::HautDroiteSortant), SDL_Rect{1408,0,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::BasDroiteSortant), SDL_Rect{1408,64,64,64} },
    {Tuile::hacher(TypeTuile::Eau, TypeJonction::Haut), SDL_Rect{1408,128,64,64} },
    // ARBRE (HERBE)        5
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautGaucheSortant), SDL_Rect{1728,0,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasGaucheSortant), SDL_Rect{1728,64,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Bas), SDL_Rect{1728,128,64,64} },

    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautDroiteSortant), SDL_Rect{1792,0,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasDroiteSortant), SDL_Rect{1792,64,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Haut), SDL_Rect{1792,128,64,64} },

    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasDroiteEntrant), SDL_Rect{1856,0,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautDroiteEntrant), SDL_Rect{1856,64,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Gauche), SDL_Rect{1856,128,64,64} },

    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::BasGaucheEntrant), SDL_Rect{1920,0,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::HautGaucheEntrant), SDL_Rect{1920,64,64,64} },
    {Tuile::hacher(TypeTuile::Arbre, TypeJonction::Droite), SDL_Rect{1920,128,64,64} },
    // HERBE                4
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::HautGaucheSortant), SDL_Rect{1728,0,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::BasGaucheSortant), SDL_Rect{1728,64,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::Bas), SDL_Rect{1728,128,64,64} },

    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::HautDroiteSortant), SDL_Rect{1792,0,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::BasDroiteSortant), SDL_Rect{1792,64,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::Haut), SDL_Rect{1792,128,64,64} },

    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::BasDroiteEntrant), SDL_Rect{1856,0,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::HautDroiteEntrant), SDL_Rect{1856,64,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::Gauche), SDL_Rect{1856,128,64,64} },

    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::BasGaucheEntrant), SDL_Rect{1920,0,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::HautGaucheEntrant), SDL_Rect{1920,64,64,64} },
    {Tuile::hacher(TypeTuile::Herbe, TypeJonction::Droite), SDL_Rect{1920,128,64,64} }
};

const std::map<int, std::map<int, SDL_Rect> > TUILE2RECT = {
    {TypeTuile::Eau, EAU},
    {TypeTuile::Arbre, ARBRE},
    {TypeTuile::Sable, SABLE},
    {TypeTuile::Herbe, HERBE},
    {TypeTuile::Beton, BETON},
    {TypeTuile::Terre, TERRE}
};


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
    static void supprimerInstance();
};

#endif // CHARGEMENTFEUILLEDESPRITES_H
