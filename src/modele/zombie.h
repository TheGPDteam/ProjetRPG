#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "personnage.h"

class Zombie : public Personnage
{
private:
    const unsigned short m_MULTIPLICATEUR_VITESSE = 100;
public:
    Zombie(int niveau);
    unsigned short obtenirVitesse() override;
};

#endif // ZOMBIE_H
