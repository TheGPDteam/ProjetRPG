#include "modele.h"
#include <utility>

using namespace std;

//! \file fichier modele
//! \date 17/11/16
//! \version 0.1

//!
//! \brief Constructeur par defaut de la classe modele
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
//! Construit un objet de la classe modele
//!

Modele::Modele()
    :m_deplacementDepuisDernierCombat{0},
      m_joueur{Joueur{Quete("Un bouquet pour ma mère","Ramasser des fleurs", 10, 50, new Vivre())}}
{
}

//!
//! \brief Accesseur en lecture du nom de la partie
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
//! Renvoit le nom de la partie
//!

std::string Modele::obtenirNomPartie() const
{
    return m_nomPartie;
}

//!
//! \brief Accesseur en ecriture du nom de la partie
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! @param nom : Nouveau nom de la partie
//!

void Modele::definirNomPartie(std::string nom)
{
    m_nomPartie=nom;
}

//!
//! \brief Modele::testerDeplacement
//! \param dir
//! \return
//!

bool Modele::testerDeplacement(Direction& dir){

    int tailleCarte = m_carte.obtenirZoneActive()->obtenirTaille();
    int posX = m_joueur.obtenirPosition().first;
    int posY = m_joueur.obtenirPosition().second;

    switch(dir){
    case Nord:
        return posY-1>=0 && m_carte.obtenirZoneActive()->obtenirTuile(make_pair(posX, posY-1))->obtenirEstMarchable();
        break;
    case Sud:
        return posY+1<tailleCarte && m_carte.obtenirZoneActive()->obtenirTuile(make_pair(posX, posY+1))->obtenirEstMarchable();
        break;
    case Ouest:
        return posX-1>=0 && m_carte.obtenirZoneActive()->obtenirTuile(make_pair(posX-1, posY))->obtenirEstMarchable();
        break;
    case Est:
        return posX+1<tailleCarte && m_carte.obtenirZoneActive()->obtenirTuile(make_pair(posX+1, posY))->obtenirEstMarchable();
        break;
    }
}


void Modele::deplacement(Direction dir)
{
    //On test si le déplacement est possible
    if(testerDeplacement(dir)){
        m_deplacementDepuisDernierCombat++;
        m_joueur.deplacerJoueur(dir);
        if(m_carte.obtenirZoneActive()->obtenirObjet(m_joueur.obtenirPosition()) != NULL)
        {
            m_joueur.obtenirInventaireJoueur()->ajouterObjet(m_carte.obtenirZoneActive()->obtenirObjet(m_joueur.obtenirPosition()));
            m_carte.obtenirZoneActive()->supprimerObjet(m_carte.obtenirZoneActive()->obtenirObjet(m_joueur.obtenirPosition()));
            (m_carte.obtenirZoneActive()->obtenirObjets().find(m_carte.obtenirZoneActive()->obtenirObjet(m_joueur.obtenirPosition())));

        }
        if (m_carte.obtenirZoneActive()->obtenirTuile(m_joueur.obtenirPosition().first,m_joueur.obtenirPosition().second)->obtenirExtremiteCarte())
        {
            // On est dans le cas où on est à une extremité de la carte qui amène vers une autre carte, on change donc la zone active en fonction
            // des coordonnées
            if (m_joueur.obtenirPosition().second==0)
            {
                m_carte.changerZoneActive(Nord);
            }
            if (m_joueur.obtenirPosition().second==64)
            {
                m_carte.changerZoneActive(Sud);
            }
            if (m_joueur.obtenirPosition().first==0)
            {
                m_carte.changerZoneActive(Ouest);
            }
            if (m_joueur.obtenirPosition().first==64)
            {
                m_carte.changerZoneActive(Est);
            }


            std::pair<int,int> nouvellePosition = m_joueur.obtenirPosition();
            switch (m_joueur.obtenirPosition().second) {
            case 63:
            {
                nouvellePosition.second = 0;
                break;
            }
            case 0:
            {
                nouvellePosition.second = 63;
                break;
            }
            default:
                break;
            }
            switch (m_joueur.obtenirPosition().first) {
            case 0:
            {
                nouvellePosition.first = 63;
                break;
            }
            case 63:
            {
                nouvellePosition.first = 0;
                break;
            }
            default:
                break;
            }
            m_joueur.definirPosition(nouvellePosition);
        }
    }
}

//!
//! \brief Permet d'avancer sur une journee, controle les etapes d'une journee
//! \author mleothaud
//! \date 17/11/16
//! \version 0.0.1
//!
//! Un survivant arrive, on choisit de le garder ou pas, on l'affecte a une quete si oui,
//! on part ensuite en quete pendant 10 minutes
//!

void Modele::journeeSuivante()
{
    //Un survivant arrive


    //On part en quête
    /*Code à faire*/
}

//!
//! \brief Permet de lancer un combat
//! \author mleothaud
//! \date 17/11/16
//! \version 0.0.2
//!

void Modele::lancerCombat()
{
    int probabilite = 95;
    if (rand()%100 < probabilite)
        Combat combat(m_joueur.obtenirEquipe());
    else
    {
        std::set<Personnage *> personnagesAdverses;
        for (int i=0; i < 4; ++i)
        {
            Humain *h = new Humain();
            personnagesAdverses.insert(h);
        }
        Equipe *e = new Equipe(personnagesAdverses);
        Combat combat(m_joueur.obtenirEquipe(), e);
    }
}

//!
//! \brief Permet la gestion de la premiere journee, differente des autres
//! \author mleothaud
//! \date 17/11/16
//! \version 0.0.1
//!
//! Doit permettre l'affichage d'un texte expliquant le scénario
//!

void Modele::premiereJournee()
{
    //TO-DO
}

//!
//! \brief Accesseur en lecture du temps
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!

Temps* Modele::obtenirTemps()
{
    return &m_temps;
}

//!
//! \brief Accesseur en ecriture du temps
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!

void Modele::definirTemps(Temps temps)
{
    m_temps=temps;
}

//!
//! \brief Accesseur en lecture de la carte
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!

Carte * Modele::obtenirCarte()
{
    return &m_carte;
}

//!
//! \brief Accesseur en ecriture de la carte
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!

void Modele::definirCarte(Carte carte)
{
    m_carte=carte;
}

//!
//! \brief Accesseur en lecture du campement
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!

Campement * Modele::obtenirCampement()
{
    return &m_campement;
}

//!
//! \brief Accesseur en ecriture du campement
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!

void Modele::definirCampement(Campement campement)
{
    m_campement=campement;
}

//!
//! \brief Accesseur en lecture du combat
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!

Combat * Modele::obtenirCombat()
{
    return &m_combat;
}

//!
//! \brief Accesseur en ecriture du combat
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!

void Modele::definirCombat(Combat combat)
{
    m_combat=combat;
}

//!
//! \brief Accesseur en lecture du joueur
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!

Joueur* Modele::obtenirJoueur()
{
    return &m_joueur;
}
//!
//! \brief Accesseur en ecriture du joueur
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!

void Modele::definirJoueur(Joueur joueur)
{
    m_joueur = joueur;
}
