#ifndef tuile_h
#define tuile_h

#include "direction.h"

enum TypeTuile {
    Sable = 0,
    Herbe,
    Eau,
    Beton,
    Terre,
    Pierre,
    Buisson,
    Tronc,
    FlecheDroite,
    FlecheGauche,
    FlecheHaut,
    FlecheBas,
    HerbeDecoration1,
    HerbeDecoration2,
    HerbeDecoration3,
    HerbeDecoration4,
    /*HerbeHerbeHerbeEau,
    HerbeHerbeEauHerbe,
    EauEauEauHerbe,
    EauEauHerbeEau,
    TerreTerreTerreEau,
    TerreTerreEauTerre,
    EauEauEauTerreEau,
    GoudronGoudronGoudronTerre,
    GoudronGoudronTerreGoudron,
    TerreTerreTerreGoudron,
    TerreTerreGoudronTerre,
    HerbeHerbeHerbe

    AucunType*/
};

enum TypeCompose {
    hey = Sable
};

class Tuile{
//protected:

private:
    TypeTuile m_type;
    Direction m_directionChangementZone;
    bool m_marchable;
    int m_numero;
public:
    Direction obtenirDirectionChangementZone() const;
    void definirDirectionChangementZone(Direction dir);
    Tuile(int val);
    bool obtenirEstMarchable() const;
    bool obtenirPeutApparaitre() const;
    int obtenirNumero() const;
};

#endif
