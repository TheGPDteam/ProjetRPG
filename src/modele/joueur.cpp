#include "joueur.h"
#include <iostream>


//! \file fichier Joueur
//! \date 17/11/16
//! \version 1.0

//!
//! \brief Attribuer une quete a un joueur
//! \return
//! \author mleothaud, fvain
//! \date 16/11/2016
//! @param prend une quete en parametre
//! \version 1.0
//!

Joueur::Joueur(const Quete &quete) :
    m_queteJoueur{quete},
    m_direction{Direction::Aucune}
{
    m_position.first=11;
    m_position.second=11;
    m_nom = "Friedrich";

    m_equipe = new Equipe(&m_personnageJoueur);
    m_inventaireJoueur = new Inventaire();


    m_tempsActuel = std::clock();
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
void Joueur::definirPosition(std::pair<int,int> nouvelle_position){
    m_position=nouvelle_position;
}


//!
//! \brief Méthode de déplacement du joueur sur la grille de la carte
//! \param dir Direction dans laquelle le joueur se déplace
//! \date 20/11/2016
//! \version 0.1
//!
void Joueur::deplacerJoueur(Direction dir){
    if ((std::clock() - m_tempsActuel) / (double) CLOCKS_PER_SEC >= TEMPS_ENTRE_DEPLACEMENT){
        switch(dir){
            case Nord:
                m_position.second--;
                break;
            case Sud:
                m_position.second++;
                break;
            case Ouest:
                m_position.first--;
                break;
            case Est:
                m_position.first++;
                break;
            default:
                break;
        }


        m_direction = dir;
        mettreAChange();
        notifierTous();
        m_direction = Direction::Aucune;
    }
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

Humain* Joueur::obtenirPersonnageJoueur(){
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

Equipe* Joueur::obtenirEquipe() const{
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

void Joueur::definirEquipe(Equipe* equipe){
    m_equipe = equipe;
}


//!
//! \brief Joueur::nouvelleQuete
//! \param quete
//! \date 18/04/17
//! \author mleothaud, fvain
//!

void Joueur::nouvelleQuete(TypeQuete tq, std::string nom, std::string description, int objectif, int experiences, Objet* recompense){
    m_queteJoueur = Quete(tq, nom, description, objectif, experiences, recompense);
}


Inventaire* Joueur::obtenirInventaire(){
    return m_inventaireJoueur;
}


Joueur::~Joueur(){
    if(m_equipe != nullptr)           delete m_equipe;
    if(m_inventaireJoueur != nullptr) delete m_inventaireJoueur;
    //if(m_camp != nullptr) delete m_camp;
}


//!
//! \brief Accesseur de la Quete du joueur
//! \return Quete* Pointeur vers la Quete du joueur
//!
Quete* Joueur::obtenirQuete() {
    return &m_queteJoueur;
}


//!
//! \brief Serialise les données de la classe Joueur
//! \return Les données de la classe joueur au format XML
//! \date 12/11/17
//! \author nlesne
//! \version 0.2
//!
std::string Joueur::serialiser() const{
    return "<Joueur>"
           "   <NomJoueur>" + m_nom + "</NomJoueur>"
                                      "   <EquipeJoueur>"
            + m_equipe->serialiser()
            +
            "   </EquipeJoueur>"
            "   <PersonnageJoueur>"
            + m_personnageJoueur.serialiser()
            +
            "   </PersonnageJoueur>"
            + m_inventaireJoueur->serialiser()
            +
            "</Joueur>";
}


void Joueur::charger(const std::string &donnees){
    m_nom = obtenirSousChaineEntre2Predicats(donnees,"<NomJoueur>","</NomJoueur>");

    std::string donneesEquipe = obtenirSousChaineEntre2Predicats(donnees,"<EquipeJoueur>","</EquipeJoueur>");
    m_equipe = new Equipe();
    m_equipe->charger(donneesEquipe);

    m_personnageJoueur.charger(obtenirSousChaineEntre2Predicats(donnees,"<PersonnageJoueur>","</PersonnageJoueur>"));

    m_inventaireJoueur = new Inventaire();
    m_inventaireJoueur->charger(obtenirSousChaineEntre2Predicats(donnees,"<Inventaire>","</Inventaire>"));
}

/*
QuetePrincipale *Joueur::obtenirQuetePrincipale() {
    return &m_quetePrincipale;
}
*/

//!
//! \brief returne la direction du joueur
//! \return la direction du joueur
//! \date 21/03/19
//! \author dolacoste
//! \version 1
//!
Direction Joueur::obtenirDirection() const {
    return m_direction;
}
