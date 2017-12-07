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
    : m_joueur{Joueur{Quete("Survivre aujourd'hui","Récolter assez de nourriture pour pouvoir passer la nuit",
                            0, 50, new Vivre())}},
      m_deplacementDepuisDernierCombat{0},
      m_nouvelArrivant(nullptr)
{
    // Calcul de la quantité de vivres à obtenir pour survivre au jour suivant. Si les vivres possédés sont supérieurs à la consommation,
    // le calcul se fait pour plusieurs jours à l'avance.
    m_joueur.obtenirQuete()->definirValeurObjectif(std::abs(m_campement.obtenirNbVivres()-m_campement.obtenirConsommation()
                                                            *m_campement.obtenirNbVivres()/(m_campement.obtenirConsommation()+1)));
    // si m_campement.obtenirNbVivres()/m_campement.obtenirConsommation() > 0 indiquer au joueur le nombre de jours d'avance
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
        if (posY==0 && m_carte.obtenirZoneActive()->obtenirTuile(make_pair(posX, posY))->obtenirExtremiteCarte())
            return true;
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
    default :
        return false;
    }
}

//!
//! \brief Permet de gérer le déplacement du personnage
//! \author mleothaud
//! \date 17/11/16
//! \version 2.0
//! @param dir : la direction du déplacement
//! A noter : présente un bug dans le changement d'une carte à une autre
//!

void Modele::deplacement(Direction dir)
{
    //On teste si le déplacement est possible
    if(testerDeplacement(dir)){
        bool veutChanger = false;
        m_deplacementDepuisDernierCombat++;
        m_joueur.deplacerJoueur(dir);
        if(m_carte.obtenirZoneActive()->obtenirObjet(m_joueur.obtenirPosition()) != NULL && !obtenirJoueur()->obtenirInventaireJoueur()->estPlein())
        {
            m_joueur.obtenirInventaireJoueur()->ajouterObjet(m_carte.obtenirZoneActive()->obtenirObjet(m_joueur.obtenirPosition()));
            m_carte.obtenirZoneActive()->supprimerObjet(m_carte.obtenirZoneActive()->obtenirObjet(m_joueur.obtenirPosition()));
            (m_carte.obtenirZoneActive()->obtenirObjets().find(m_carte.obtenirZoneActive()->obtenirObjet(m_joueur.obtenirPosition())));

            /*****************************************/
           /*Partie a changer car segmentation fault*/
          /*****************************************/

            //std::cout << "obj is of type " << typeid(obj).name() << std::endl;
            TypeObjet to = (m_carte.obtenirZoneActive()->obtenirObjets().find(m_carte.obtenirZoneActive()->obtenirObjet(m_joueur.obtenirPosition()))->first)->obtenirType();
            if (to == TypeObjet::Objet) {

            } else if (to == TypeObjet::Arme) {

            } else if (to == TypeObjet::Vivre) {

            }


            //obj->obtenirType();

            /*Vivre* v = dynamic_cast<Vivre*>(&obj);
            if (v != nullptr) {
            m_joueur.obtenirQuete()->definirValeurObjectif(m_joueur.obtenirQuete()->obtenirValeurObjectif()-
                                                           m_joueur.obtenirQuete()->obtenirValeurAvancement()-
                                                           v->obtenirValeurNutritive());
            //Modification objectif (verifier quete recolte)
            }*/
        }
        if (m_carte.obtenirZoneActive()->obtenirTuile(m_joueur.obtenirPosition().first,m_joueur.obtenirPosition().second)->obtenirExtremiteCarte())
        {
            // On est dans le cas où on est à une extremité de la carte qui amène vers une autre carte, on change donc la zone active en fonction
            // des coordonnées
            // On vérifie que le joueur veuille clairement changer de zone en regardant la direction dans laquelle il souhaite aller
            if (m_joueur.obtenirPosition().second==0 && dir == 0)
            {
                veutChanger = true;
                m_carte.changerZoneActive(Nord);
            }
            if (m_joueur.obtenirPosition().second==63 && dir == 1)
            {
                veutChanger = true;
                m_carte.changerZoneActive(Sud);
            }
            if (m_joueur.obtenirPosition().first==0 && dir == 3)
            {
                veutChanger = true;
                m_carte.changerZoneActive(Ouest);
            }
            if (m_joueur.obtenirPosition().first==63 && dir == 2)
            {
                veutChanger = true;
                m_carte.changerZoneActive(Est);
            }

            if (veutChanger)
            {

                std::pair<int,int> nouvellePosition = m_joueur.obtenirPosition();
                switch (m_joueur.obtenirPosition().second) {
                case 63:
                {
                    nouvellePosition.first = m_joueur.obtenirPosition().first;
                    nouvellePosition.second = 0;
                    break;
                }
                case 0:
                {
                    nouvellePosition.first = m_joueur.obtenirPosition().first;
                    nouvellePosition.second = 63;
                    break;
                }
                }
                switch (m_joueur.obtenirPosition().first) {
                case 0:
                {
                    nouvellePosition.second = m_joueur.obtenirPosition().second;
                    nouvellePosition.first = 63;
                    break;
                }
                case 63:
                {
                    nouvellePosition.second = m_joueur.obtenirPosition().second;
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

Humain Modele::journeeSuivante()
{
    m_nouvelArrivant = new Humain();

    m_temps.reinitialiserTemps();

    return *m_nouvelArrivant;
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
//! \version 0.1
//!
//! Création d'une équipe de sept personnages
//!

void Modele::premiereJournee()
{
    for(int i=0 ; i<7 ; i++) {
        Humain *h = new Humain();
        m_campement.obtenirNonAttribuees().insert(h);
    }


    m_temps.reinitialiserTemps();
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

//!
//! \brief Serialise les attributs du modèle
//! \return Chaine contenant les attributs du modèle au format XML
//! \author nlesne
//! \date 12/11/17
//! \version 0.1
//!

std::string Modele::serialiser() const
{
    return "<Modele>\n"
            + m_campement.serialiser()
            + m_joueur.serialiser()
            +
            "   <NomPartie>\n" + m_nomPartie + "\n</NomPartie>\n"
            "</Modele>\n";
}

void Modele::charger(std::string donnees)
{

}
