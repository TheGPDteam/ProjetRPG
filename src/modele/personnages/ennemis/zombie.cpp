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
    m_vitesse.definirValeur((rand()%m_vitesse.obtenirValeurMax()) / 2 + 1);
    m_vitesse.augmenter(niveau);
}

//!
//! \brief Accesseur en lecture de la vitesse
//! \return la vitesse du zombie
//! \author mleothaud, parMarius
//! \date 17/11/2016 - 06/11/2017
//! \version 1.0
//!

unsigned short Zombie::obtenirVitesse() {
    return m_vitesse.obtenirValeur() * m_MULTIPLICATEUR_VITESSE_BASE_ARME;
}

unsigned short Zombie::obtenirDegats()
{
    srand(time(nullptr));
    if (rand() < m_CHANCE_DE_MANQUER)
        return 0;
    else
        return this->Personnage::obtenirDegats();
}

