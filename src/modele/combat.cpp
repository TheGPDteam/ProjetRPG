#include "combat.h"
#include <algorithm>

//! \file fichier combat
//! \date 17/11/16
//! \version 1.0

bool comparerVitesse(Personnage* p1, Personnage* p2) {
    return (p1->obtenirVitesse() > p2->obtenirVitesse());
}

//!
//! \brief Constructeur paramétré de combats nécessitant deux équipes
//! \param equipeHaute : une équipe
//! \param equipeBasse : une autre équipe
//! \author mleothaud
//! \version 1.1
//!

Combat::Combat(Equipe *equipeHaute, Equipe *equipeBasse)
    :m_numeroDePassage{0}, m_equipeBasse{equipeBasse},m_equipeHaute{equipeHaute},m_ordrePassage{nullptr}
{
    int i=0;
    for (Personnage* p : *m_equipeHaute)
    {
        if (p->obtenirVie()->obtenirValeur()!=0)
        {
            m_ordrePassage[i] = p;
            ++i;
        }
    }
    for (Personnage *p : *m_equipeBasse)
    {
        if (p->obtenirVie()->obtenirValeur()!=0)
        {
            m_ordrePassage[i] = p;
            ++i;
        }
    }
    std::sort(m_ordrePassage.begin(),m_ordrePassage.end(), comparerVitesse);
}

//!
//! \brief Constructeur paramétré de combats nécessitant une équipe
//! \param equipeHaute : une équipe
//! \author mleothaud
//! \version 1.1
//!
//! La seconde équipe est générée automatiquement par la fonction "genererEquipeZombie"
//!


Combat::Combat(Equipe *equipeHaute)
    :m_numeroDePassage{0},m_equipeHaute{equipeHaute},m_ordrePassage{nullptr}
{
    int i=0;
    for (Personnage* p : *m_equipeHaute)
    {
        if (p->obtenirVie()->obtenirValeur()!=0)
        {
            m_ordrePassage[i] = p;
            ++i;
        }
    }
    m_equipeBasse->genererEquipeZombie();
    for (Personnage* p : *m_equipeBasse)
    {
        if (p->obtenirVie()->obtenirValeur()!=0)
        {
            m_ordrePassage[i] = p;
            ++i;
        }
    }
    std::sort(m_ordrePassage.begin(),m_ordrePassage.end(), comparerVitesse);
}

//!
//! \brief Accesseur en lecture de l'equipe basse
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return un pointeur vers l'attribut equipeBasse du combat
//!

Equipe* Combat::obtenirEquipeBasse() const
{
    return m_equipeBasse;
}

//!
//! \brief Accesseur en lecture de l'equipe haute
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return un pointeur vers l'attribut equipeHaute du combat
//!

Equipe* Combat::obtenirEquipeHaute() const
{
    return m_equipeHaute;
}

//!
//! \brief Permet de passer au tour suivant et d'avancer dans le combat
//! \author mleothaud
//! \date 17/11/16
//! \version 0.1
//!
//! Augmente le numero de passage, manque à effectuer les actions
//!

void Combat::tourSuivant()
{
    m_numeroDePassage++;
}


//!
//! \brief Permet d'effectuer l'attaue prévue
//! \author mleothaud
//! \date 16/03/17
//! \version 1.0
//!

void Combat::effectuerAttaque(Personnage *agresseur, Personnage *cible)
{
    cible->obtenirVie()->diminuer(agresseur->obtenirDegats());
}

//!
//! \brief Permet d'ajouter une action au combat
//! \author mleothaud
//! \date 16/03/17
//! \version 0.1
//!
//! Ajoute l'action à faire pour le tour
//!

void Combat::ajouterAction(Personnage* cible, Personnage* source, ActionCombat action)
{
    if (!source->obtenirVie()->obtenirValeur()==0)
    {

        switch (action)
        {
        case AUCUNE :
        {
            break;
        }
        case ATTAQUER:
        {
            m_actionDuTour.first=std::make_pair(cible,source);
            m_actionDuTour.second=ATTAQUER;
            break;
        }
        }
    }
}

//!
//! \brief Permet de connaitre le prochain personnage à effectuer une action
//! \author mleothaud
//! \date 16/03/17
//! \version 0.1
//! \return le prochain personnage à jouer
//!

Personnage* Combat::prochainPersonnage()
{
    if (m_numeroDePassage==0)
    {
        return m_ordrePassage[0];
    }
    else
    {
        ++m_numeroDePassage;
        m_numeroDePassage=m_numeroDePassage%8;
        return m_ordrePassage[m_numeroDePassage];
    }
}
