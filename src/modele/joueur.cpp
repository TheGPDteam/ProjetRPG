#include "joueur.h"
#include <iostream>


//! \file fichier Joueur
//! \date 17/11/16
//! \version 1.0

//!
//! \brief initialise un joueur
//! \author mleothaud
//! \date 16/11/2016
//! \version 0.1
//! Contient l'initialisation des attributs de joueur
//!

Joueur::Joueur()
{
    m_position.first=25;
    m_position.second=25;
    m_nom = "Ali Baba";
    m_camp = new Campement();
    m_equipe = new Equipe();
}

//!
//! \brief Attribuer une quete a un joueur
//! \return
//! \author mleothaud, fvain
//! \date 16/11/2016
//! @param prend une quete en parametre
//! \version 1.0
//!

Joueur::Joueur(Quete quete) :
    m_queteJoueur{quete}
{
    m_position.first=5;
    m_position.second=5;
    m_nom = "Ali Baba";
    m_camp = new Campement();
    m_equipe = new Equipe();
    m_inventaireJoueur = new Inventaire();
}

//!
//! \brief Attribuer une quete a un joueur
//! \return
//! \author mleothaud, fvain
//! \date 16/11/2016
//! @param prend une quete en parametre
//! @param prend un nom en paramètre
//! \version 1.0
//!

Joueur::Joueur(Quete quete, std::string nom) :
    m_queteJoueur{quete}, m_nom{nom}
{
    m_position.first=5;
    m_position.second=5;
    m_camp = new Campement();
    m_equipe = new Equipe();
    m_inventaireJoueur = new Inventaire();
}

//!
//! \brief Obtenir la position d'un joueur
//! \return position du joueur sous la forme de couple
//! \author mleothaud
//! \date 16/11/2016
//! @param aucun
//! \version 1.0
//! Contient retour de position du joueur
//!

std::pair<int,int> Joueur::obtenirPosition() const
{
    return m_position;
}

//!
//! \brief Obtenir le nom d'un joueur
//! \return nom du joueur
//! \author mleothaud
//! \date 16/11/2016
//! @param aucun
//! \version 1.0
//! Contient retour du nom
//!

std::string Joueur::obtenirNom() const
{
    return m_nom;
}

//!
//! \brief Attribuer une nouvelle position
//! \return rien
//! \author mleothaud
//! \date 16/11/2016
//! @param la nouvelle position sous forme de couple d'entier
//! \version 1.0
//! Contient une affectation de variable
//!

void Joueur::definirPosition(std::pair<int,int> nouvellePosition)
{
    m_position=nouvellePosition;
}

//!
//! \brief Méthode de déplacement du joueur sur la grille de la carte
//! \param dir Direction dans laquelle le joueur se déplace
//! \date 20/11/2016
//! \version 0.1
//!

void Joueur::deplacerJoueur(Direction dir){
    switch(dir){
    case Nord:
    {
        m_position.second--;
        break;
    }
    case Sud:
    {
        m_position.second++;
        break;
    }
    case Ouest:
    {
        m_position.first--;
        break;
    }
    case Est:
    {
        m_position.first++;
        break;
    }
    }

    mettreAChange();
    notifierTous();
}

//!
//! \brief definir nom joueur
//! \return rien
//! \author mleothaud
//! \date 16/11/2016
//! @param une chaine de caractères
//! \version 1.0
//! Contient affectation de variable
//!

void Joueur::definirNom(std::string nom)
{
    m_nom = nom;
}

//!
//! \brief attribuer au joueur son personnage
//! \return le personnage du joueur
//! \author mleothaud
//! \date 16/11/2016
//! @param aucun
//! \version 1.0
//! Contient retour du personnage du joueur
//!

Humain* Joueur::obtenirPersonnageJoueur()
{
    return &m_personnageJoueur;
}

//!
//! \brief Attribuer une equipe au joueur
//! \return return l'équipe
//! \author mleothaud
//! \date 16/11/2016
//! @param aucun
//! \version 1.0
//! Contient retour de l'equipe du joueur
//!

Equipe* Joueur::obtenirEquipe() const
{
    return m_equipe;
}

//!
//! \brief definir l'équipe du joueur
//! \return position du joueur sous la forme de couple
//! \author mleothaud
//! \date 16/11/2016
//! @param element equipe de type equipe
//! \version 1.0
//! Contient affectation de variable
//!

void Joueur::definirEquipe(Equipe* equipe)
{
    m_equipe=equipe;
}

//!
//! \brief Joueur::nouvelleQuete
//! \param quete
//! \date 18/04/17
//! \author mleothaud, fvain
//!

void Joueur::nouvelleQuete(Quete quete){
    m_queteJoueur = quete;
}

Inventaire* Joueur::obtenirInventaireJoueur()
{
    return m_inventaireJoueur;
}

Joueur::~Joueur()
{
    if(m_equipe != nullptr)
    {
        delete m_equipe;
    }
    if(m_inventaireJoueur != nullptr)
    {
        delete m_inventaireJoueur;
    }
    if(m_camp != nullptr)
    {
        delete m_camp;
    }
}

//!
//! \brief Accesseur de la Quete du joueur
//! \return Quete* Pointeur vers la Quete du joueur
//!

Quete* Joueur::obtenirQuete() {
    return &m_queteJoueur;
}
