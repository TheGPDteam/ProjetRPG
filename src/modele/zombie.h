#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "personnage.h"

class Zombie : public Personnage
{
public:
    Zombie(int niveau);
    unsigned short obtenirVitesse() override;
};

#endif // ZOMBIE_H
