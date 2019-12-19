#ifndef ZONECHANGEMENTZONE_H
#define ZONECHANGEMENTZONE_H
#include "joueur.h"

class ZoneChangementZone
{
public:
    ZoneChangementZone(int pos1X, int pos1Y, int pos2X, int pos2Y, Direction dir, int arriveX, int arriveY);
    bool estSur(Joueur * joueur);
    Direction obtenirDirection();
    std::pair<int,int> obtenirPositionArrive();
private:
    int pos1X;
    int pos1Y;
    int pos2X;
    int pos2Y;
    Direction dir;

    int arriveX;
    int arriveY;
};

#endif // ZONECHANGEMENTZONE_H
