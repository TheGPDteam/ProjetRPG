#include "zonechangementzone.h"

ZoneChangementZone::ZoneChangementZone(int pos1X, int pos1Y, int pos2X, int pos2Y, Direction dir, int arriveX, int arriveY)
{
    this->pos1X = pos1X;
    this->pos1Y = pos1Y;
    this->pos2X = pos2X;
    this->pos2Y = pos2Y;
    this->dir = dir;
    this->arriveX = arriveX;
    this->arriveY = arriveY;
}

bool ZoneChangementZone::estSur(Joueur * joueur){
    int x = joueur->obtenirPosition().first;
    int y = joueur->obtenirPosition().second;

    return (x >= pos1X && x <= pos2X && y >= pos1Y && y <= pos2Y);
}

Direction ZoneChangementZone::obtenirDirection(){
    return dir;
}

std::pair<int,int> ZoneChangementZone::obtenirPositionArrive(){
    return std::make_pair(arriveX, arriveY);
}
