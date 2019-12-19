#ifndef carte_h
#define carte_h

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "direction.h"
#include "zone.h"
#include "observable.h"

class Carte: public Observable
{
private:
    /*std::vector <Zone> m_zones;*/
    std::vector<Zone*> m_zones;
    Zone* m_zoneActive;
    unsigned short m_numZoneActive;
    void chargerZone(std::string nom_fichier_zone);
public :
    Carte();
    ~Carte();
    void definirObservateurZones(Observateur &obs);
    Zone *obtenirZoneActive();
    void changerZoneActive(int numeroZone);
    void recharger();
    void zoneActiveCampement();
};

#endif
