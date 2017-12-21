#ifndef tuile_h
#define tuile_h

#include "direction.h"

enum TypeTuile {
    Eau=0,
    Sable,
    Herbe,
    Beton,
    Terre,
    Arbre
};


class Tuile
{
protected:
    TypeTuile m_type;
private:
    Direction m_directionChangementZone;
public:
    Direction obtenirDirection() const;
    void definirDirection(Direction dir);
    Tuile(int val);
    TypeTuile obtenirType() const;
    bool obtenirEstMarchable() const;
    bool obtenirPeutApparaitre() const;
};

#endif
