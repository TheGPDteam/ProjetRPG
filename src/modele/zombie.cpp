#include "zombie.h"

//! \file fichier zombie
//! \date 17/11/16
//! \version 1.0

Zombie::Zombie(int niveau)
{
    m_force.definirValeur((rand()%m_force.obtenirValeurMax()) + 1);
    m_force.augmenter(niveau);
    m_intelligence.definirValeur((rand()%m_intelligence.obtenirValeurMax()) + 1);
    m_intelligence.augmenter(niveau);
    m_vitesse.definirValeur((rand()%m_vitesse.obtenirValeurMax()) + 1);
    m_vitesse.augmenter(niveau);
}

unsigned short Zombie::obtenirVitesse() {
    return m_vitesse.obtenirValeur()*m_MULTIPLICATEUR_VITESSE;
}

