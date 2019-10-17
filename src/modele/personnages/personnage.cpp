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
    : m_vie{(rand()%100)+1}
{}

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

Personnage::Personnage(int force, int intelligence, int vitesse, int vie_maximale)
{
    m_force.definirValeur(force);
    m_intelligence.definirValeur(intelligence);
    m_vitesse.definirValeur(vitesse);
    m_vie.definirValeurMax(vie_maximale);
    m_vie.definirValeur(vie_maximale);
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

//!
//! \brief Accesseur en lecture des dégats + coups critiques
//! \return la vie du personnage
//! \author mleothaud, mpardo
//! \date 17/11/2016 - 26/10/2017
//! \version 2.0
//!

unsigned short Personnage::obtenirDegats()
{
    bool coupCritique = (rand() % 101) < m_CHANCE_CC_BASE + (2) * m_intelligence.obtenirValeur(); // ([Chance CC de Base]​ + [Multiplicateur CC]​ * [Point d’intelligence])
    if(coupCritique){
        return m_force.obtenirValeur() + (m_force.obtenirValeur() / 2);
    }
    else{
        return m_force.obtenirValeur();
    }
}

//!
//! \brief Méthode virtuelle de serialisation des personnages
//! \author nlesne
//! \date 16/10/17
//! \version 1.0
//! \return Vecteur Vide
//!

std::string Personnage::serialiser() const
{
    return {};
}

