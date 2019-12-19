#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "../personnage.h"

class Zombie : public Personnage
{
private:
    const unsigned short m_MULTIPLICATEUR_VITESSE_BASE_ARME = 100;
    const static unsigned short m_CHANCE_DE_MANQUER = 0.5;
public:
    Zombie(int niveau);
    unsigned short obtenirVitesse() override;
    unsigned short obtenirDegats() override;
};

#endif // ZOMBIE_H
