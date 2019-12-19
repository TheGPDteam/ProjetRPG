#include "zonechangementzone.h"

ZoneChangementZone::ZoneChangementZone(int pos1X, int pos1Y, int pos2X, int pos2Y, int numeroZone, int arriveX, int arriveY)
{
    this->m_pos1X = pos1X;
    this->m_pos1Y = pos1Y;
    this->m_pos2X = pos2X;
    this->m_pos2Y = pos2Y;
    this->m_numeroZone = numeroZone;
    this->m_arriveX = arriveX;
    this->m_arriveY = arriveY;
}

bool ZoneChangementZone::estSur(Joueur * joueur){
    int x = joueur->obtenirPosition().first;
    int y = joueur->obtenirPosition().second;

    return (x >= m_pos1X && x <= m_pos2X && y >= m_pos1Y && y <= m_pos2Y);
}


int ZoneChangementZone::obtenirNumeroZone(){
    return m_numeroZone;
}

std::pair<int,int> ZoneChangementZone::obtenirPositionArrive(){
    return std::make_pair(m_arriveX, m_arriveY);
}
