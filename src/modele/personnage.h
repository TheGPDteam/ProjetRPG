#ifndef personnage_h
#define personnage_h

#include "statistique.h"
#include "vie.h"

class Personnage
{
protected:
    static int const m_CHANCE_CC_BASE = 10;
    Statistique m_force;
    Statistique m_intelligence;
    Statistique m_vitesse;
    Vie m_vie;
public:
    Personnage();
    Personnage(int valeurForce, int valeurIntelligence, int valeurVitesse, int vieMax);
    Statistique* obtenirForce();
    Statistique* obtenirIntelligence();
    Vie* obtenirVie();
    virtual unsigned short obtenirVitesse()=0;
    virtual unsigned short obtenirDegats();
    virtual std::string serialiser() const;
};

#endif
