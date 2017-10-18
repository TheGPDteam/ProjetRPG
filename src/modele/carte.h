#ifndef carte_h
#define carte_h

#include <string>
#include "zone.h"
#include "observable.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "direction.h"

const int TAILLE_CARTE_X = 3;
const int TAILLE_CARTE_Y = 3;

class Carte: public Observable
{
private:
    /*std::vector <Zone> m_zones;*/
    Zone* m_zones[TAILLE_CARTE_X][TAILLE_CARTE_Y];
    Zone* m_zoneActive;
    unsigned short m_xZoneActive;
    unsigned short m_yZoneActive;
    void chargerZone(std::string nomZone, short x, short y);
public :
    Carte();
    ~Carte();
    Zone *obtenirZoneActive();
    void changerZoneActive(Direction direction);
};

#endif
