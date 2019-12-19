#ifndef ZONECHANGEMENTZONE_H
#define ZONECHANGEMENTZONE_H
#include "joueur.h"

class ZoneChangementZone
{
public:
    ZoneChangementZone(int pos1X, int pos1Y, int pos2X, int pos2Y, int numeroZone, int arriveX, int arriveY);
    bool estSur(Joueur * joueur);
    int obtenirNumeroZone();
    std::pair<int,int> obtenirPositionArrive();
private:
    int m_pos1X;
    int m_pos1Y;
    int m_pos2X;
    int m_pos2Y;

    int m_numeroZone;
    int m_arriveX;
    int m_arriveY;
};

#endif // ZONECHANGEMENTZONE_H
