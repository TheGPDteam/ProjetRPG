#include "personnage.h"

//! \file fichier personnage
//! \date 17/11/16
//! \version 1.0

//!
//! \brief Constructeur par defaut
//! \author mleothaud
//! \date 17/11/2016
//! @param aucun
//! \version 1.0
//! Affecte tous les attributs du personnage à 1
//!

Personnage::Personnage()
{
    m_force.definirValeur(1);
    m_intelligence.definirValeur(1);
    m_vitesse.definirValeur(1);
    m_vie.definirValeur(1);
    m_vie.definirValeurMax(1);
}

//!
//! \brief Constructeur parametre du personnage
//! \author mleothaud
//! \date 17/11/2016
//! @param Force : Sa nouvelle force
//! @param Intelligence : Sa nouvelle intelligence
//! @param Vitesse : Sa nouvelle vitesse
//! @param vieMax : Sa nouvelle vie maximum et sa nouvelle vie
//! \version 1.0
//! Contient affectations des différentes valeurs aux attributs
//!

Personnage::Personnage(int valeurForce, int valeurIntelligence, int valeurVitesse, int vieMax)
{
    m_force.definirValeur(valeurForce);
    m_intelligence.definirValeur(valeurIntelligence);
    m_vitesse.definirValeur(valeurVitesse);
    m_vie.definirValeurMax(vieMax);
    m_vie.definirValeur(vieMax);
}

//!
//! \brief Accesseur en lecture de la force
//! \return la force du personnage
//! \author mleothaud
//! \date 17/11/2016
//! \version 1.0
//!

Statistique* Personnage::obtenirForce()
{
    return &m_force;
}

//!
//! \brief Accesseur en lecture de l'intelligence
//! \return l'intelligence du personnage
//! \author mleothaud
//! \date 17/11/2016
//! \version 1.0
//!

Statistique* Personnage::obtenirIntelligence()
{
    return &m_intelligence;
}

//!
//! \brief Accesseur en lecture de la vie
//! \return la vie du personnage
//! \author mleothaud
//! \date 17/11/2016
//! \version 1.0
//!

Vie* Personnage::obtenirVie()
{
    return &m_vie;
}

unsigned short Personnage::obtenirDegats()
{
    return m_force.obtenirValeur();
}

std::vector<std::string> Personnage::serialiser() const
{
    return {};
}
