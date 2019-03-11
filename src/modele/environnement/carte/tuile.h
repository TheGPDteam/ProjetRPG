#ifndef tuile_h
#define tuile_h

#include "direction.h"

enum TypeTuile {
    Eau=0,
    Sable,
    Herbe,
    Beton,
    Terre,
    Arbre,
    AucunType
};

enum TypeJonction{
    AucuneJonction,
    HautGaucheEntrant,
    HautDroiteSortant,
    HautDroiteEntrant,
    BasDroiteSortant,
    BasDroiteEntrant,
    BasGaucheSortant,
    BasGaucheEntrant,
    Haut,
    Gauche,
    Droite,
    Bas,
    HautGaucheSortant
};

class Tuile
{
//protected:

private:
    TypeTuile m_type;
    Direction m_directionChangementZone;
    int m_jonction;
    bool m_marchable;
public:
    Direction obtenirDirectionChangementZone() const;
    void definirDirectionChangementZone(Direction dir);
    Tuile(int val, bool marchable = true);
    TypeTuile obtenirType() const;
    bool obtenirEstMarchable() const;
    bool obtenirPeutApparaitre() const;

    void definirHachageJonction(TypeTuile typeVoisin, TypeJonction positionVoisin);
    int obtenirHachageJonction() const;

    static int hacher(TypeTuile typeVoisin, TypeJonction positionVoisin);
};

#endif
