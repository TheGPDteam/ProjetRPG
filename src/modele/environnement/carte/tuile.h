#ifndef tuile_h
#define tuile_h

#include "direction.h"

enum TypeTuile {
    Sable = 0,
    Herbe,
    Eau,
    Beton,
    Terre,
    Arbre,
    AucunType
};

class Tuile{
//protected:

private:
    TypeTuile m_type;
    Direction m_directionChangementZone;
    bool m_marchable;
public:
    Direction obtenirDirectionChangementZone() const;
    void definirDirectionChangementZone(Direction dir);
    Tuile(int val, bool marchable = true);
    bool obtenirEstMarchable() const;
    bool obtenirPeutApparaitre() const;
};

#endif
