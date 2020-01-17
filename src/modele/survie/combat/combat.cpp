#include "combat.h"
#include <algorithm>

//! \file fichier combat
//! \date 17/11/16
//! \version 1.0

const float Combat::PROBABILITE_OBTENIR_OBJET = 0.9;
const float Combat::PROBABILITE_OBTENIR_ARME = 0.05;

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

Combat::Combat(Equipe *equipe_haute, Equipe *equipe_basse)
    : m_equipeBasse(equipe_basse),
      m_equipeHaute{equipe_haute},
      m_ordrePassage{nullptr},
      m_numeroDePassage{0},
      m_actionDuTour{nullptr}
{
    m_ordrePassage.clear();
    for (Personnage* p : *m_equipeHaute)
    {
        if (p->obtenirVie()->obtenirValeur()!=0)
            m_ordrePassage.push_back(p);
    }
    for (Personnage *p : *m_equipeBasse)
    {
        if (p->obtenirVie()->obtenirValeur()!=0)
            m_ordrePassage.push_back(p);
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


Combat::Combat(Equipe *equipe_haute)
    : m_equipeBasse(Equipe::genererEquipeZombie()),
      m_equipeHaute(equipe_haute),
      m_ordrePassage{nullptr},
      m_numeroDePassage(0),
      m_actionDuTour{nullptr}
{
    m_ordrePassage.clear();
    for (Personnage* p : *m_equipeHaute)
    {
        if (p->obtenirVie()->obtenirValeur()!=0)
            m_ordrePassage.push_back(p);
    }
    for (Personnage *p : *m_equipeBasse)
    {
        if (p->obtenirVie()->obtenirValeur()!=0)
            m_ordrePassage.push_back(p);
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
//! \brief Combat::obtenirEquipe
//! \param personnage
//! \return
//!
Equipe* Combat::obtenirEquipe(Personnage* personnage) const
{
    if(m_equipeBasse->obtenirListePersonnage().count(personnage) == 1)
        return m_equipeBasse;
    else if (m_equipeHaute->obtenirListePersonnage().count(personnage) == 1)
        return m_equipeHaute;
    return nullptr;
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

void effectuerAttaque(Personnage *agresseur, Personnage *cible)
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

void Combat::ajouterAction(Personnage* cible, Personnage* source, TypeActionCombat action)
{
    if (!(source->obtenirVie()->obtenirValeur()==0))
    {

        switch (action)
        {
        case AUCUNE :
        {
            break;
        }
        case ATTAQUER:
        {
            m_actionDuTour = new ActionCombat(action, source, cible);
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
        ++m_numeroDePassage;
        return *m_ordrePassage.begin();
    }
    else
    {
        ++m_numeroDePassage;
        m_numeroDePassage = m_numeroDePassage % m_ordrePassage.size();
        return m_ordrePassage.at(m_numeroDePassage);
    }
}


void Combat::suprimmerPersonnageOrdrePassage(Personnage* personnage)
{
    auto it = std::find(m_ordrePassage.begin(), m_ordrePassage.end(), personnage);
    m_ordrePassage.erase(it);
}
//!
//! \brief Simulation d'un combat
//! \author nlesne
//! \date 06/12/19
//! \version 0.1
//!

void Combat::simulerCombat()
{
    Personnage* courant = *m_ordrePassage.begin();
    while(!m_equipeBasse->estMorte() && !m_equipeHaute->estMorte())
    {
        Equipe* equipeCourante = obtenirEquipe(courant);
        Personnage* cible;
        if (equipeCourante == m_equipeBasse)
        {
            cible = *m_equipeHaute->begin();
            effectuerAttaque(courant, cible);
            if (cible->obtenirVie()->obtenirValeur() <= 0)
            {
                m_equipeHaute->supprimerPersonnage(cible);
                suprimmerPersonnageOrdrePassage(cible);
            }
        }
        else
        {
            cible = *m_equipeBasse->begin();
            effectuerAttaque(courant, cible);
            if (cible->obtenirVie()->obtenirValeur() <= 0)
            {
                m_equipeBasse->supprimerPersonnage(cible);
                suprimmerPersonnageOrdrePassage(cible);
            }
        }

        courant = prochainPersonnage();
    }
}


//!
//! \brief Donne la récompense du combat
//! \return
//!
Objet* Combat::obtenirRecompense() const
{
    Objet* recompense = nullptr;
    srand(time(nullptr));
    bool tirageObjet = (rand()*1./RAND_MAX) < PROBABILITE_OBTENIR_OBJET;
    if (tirageObjet)
    {
        bool estArme = (rand()*1./RAND_MAX) < PROBABILITE_OBTENIR_ARME;
        if (estArme)
        {
            recompense = new Arme();
        }
        else
        {
            recompense = new ObjetQuetePrincipale();
        }
    }
    return recompense;
}
