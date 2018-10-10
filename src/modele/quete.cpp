#include "quete.h"

//! \file fichier quete
//! \date 17/11/16
//! \version 1.0

//!
//! \brief Constructeur paramétré
//! \date 10/11/16
//! \author mleothaud
//! @param nom string Nom de la quête
//! @param description string Description de la quête
//! @param valeurObjectif int Objectif à atteindre pour la quête
//! @param recompenseExperience int Nombre de points d'expérience gagnés à la completion de la quête
//! @param *recompense Objet Objet donné en récompense à la completion de la quête
//! \version 0.1
//!
//! Constructeur paramétré de la classe Quete
//!

Quete::Quete(TypeQuete tq, std::string nom, std::string description, int valeurObjectif, int recompenseExperience, Objet *recompense)
    :m_fini{false}, m_nom{nom}, m_description{description}, m_valeurObjectif{valeurObjectif}, m_valeurActuelle{0},
      m_recompenseExperience{recompenseExperience}, m_recompense{recompense}, m_type{tq}
{
}

//!
//! \brief Destructeur
//! \date 10/10/18
//! \author rbourqui
//! \version 0.1
//!
//! Destructeur de la classe Quete
//!

Quete::~Quete(){}

//!
//! \brief Accesseur récompense
//! \date 10/11/16
//! \version 1.0
//! \author mleothaud
//!
//! Accesseur de la récompense de la quête
//!

Objet* Quete::obtenirRecompense() const
{
    return m_recompense;
}

//!
//! \brief Accesseur récompenseExp
//! \date 10/11/16
//! \version 1.0
//! \author mleothaud
//!
//! Accesseur de la récompense en expérience de la quête
//!

int Quete::obtenirRecompenseExp() const
{
    return m_recompenseExperience;
}

//!
//! \brief Putateur objectif
//! \date 20/11/17
//! \version 1.0
//! \author adeguilhem
//! \param Nouvelle valeur de l'objectif
//!

void Quete::definirValeurObjectif(int valeur)
{
    m_valeurObjectif = valeur;
}

//!
//! \brief Mutateur récompense
//! \date 10/11/16
//! \version 1.0
//! \author mleothaud
//!
//! Mutateur de l'objet en récompense de la quête
//!

void Quete::definirRecompense(Objet obj)
{
    m_recompense=&obj;
}

//!
//! \brief Mutateur récompenseExp
//! \date 10/11/16
//! \version 1.0
//! \author mleothaud
//!
//! Mutateur de la récompense en expérience de la quête
//!

void Quete::definirRecompenseExp(int valeur)
{
    m_recompenseExperience=valeur;
}

//!
//! \brief Mutateur demarrerTimer
//! \date 19/01/17
//! \version 1.0
//! \author mleothaud
//!
//! Demarre le timer de la quete
//!

void Quete::demarrerTimer()
{
    m_tempsDebutQuete = clock();
}

//!
//! \brief QueteTerminee
//! \date 19/01/17
//! \version 1.0
//! \author mleothaud
//! \return si la quete est finie
//!
//! Retourne si la quete est terminee
//!

bool Quete::queteTerminee()
{
    double secondesEcoulees;
    secondesEcoulees = (clock() - m_tempsDebutQuete) / CLOCKS_PER_SEC;
    if (secondesEcoulees-m_secondesJeuPause>600)
        return true;
    else
        return false;
}

//!
//! \brief ObtenirTemps
//! \date 19/01/17
//! \version 1.0
//! \author mleothaud
//! \return un sting avec le temps restant
//!
//! Retourne le temps qu'il reste sous la forme d'un string
//!

std::string Quete::obtenirStringTemps()
{
    std::string retourne="";
    int secondes;
    int minutes;
    minutes = ((clock() - m_tempsDebutQuete) / CLOCKS_PER_SEC) - m_secondesJeuPause / 60;
    secondes = ((clock() - m_tempsDebutQuete) / CLOCKS_PER_SEC) - (minutes * 60) - m_secondesJeuPause;
    retourne += std::to_string(minutes);
    retourne += " : ";
    retourne += std::to_string(secondes);
    return retourne;
}

//!
//! \brief miseEnPause
//! \date 19/01/17
//! \version 1.0
//! \author mleothaud
//!
//! met le jeu en pause
//!

void Quete::miseEnPause()
{
    m_tempsDebutPause = clock();
}

//!
//! \brief ObtenirTemps
//! \date 19/01/17
//! \version 1.0
//! \author mleothaud
//! \return un sting avec le temps restant
//!
//! Retourne le temps qu'il reste sous la forme d'un string
//!

void Quete::reprise()
{
    m_secondesJeuPause = (clock() - m_tempsDebutPause) / CLOCKS_PER_SEC;
}

int Quete::obtenirValeurAvancement() const {
    return m_valeurActuelle;
}

int Quete::obtenirValeurObjectif() const {
    return m_valeurObjectif;
}

//!
//! \brief augmentValeur
//! \date 19/01/17
//! \version 1.0
//! \author dberrouet
//!
//! Augmente la valeur de la progression de l'objectif
//!

void Quete::augmenterValeur(int valeur) {
    m_valeurActuelle += valeur;
}

bool Quete::estfini()
{
    return m_fini;
}

void Quete::finir()
{
    m_fini = true;
}

TypeQuete Quete::obtenirType() const {
    return m_type;
}
