#include "equipe.h"

//! \file fichier Competence
//! \date 17/11/16
//! \version 1.0

//!
//! \brief Ajout d'un personnage a une equipe
//! \author mleothaud
//! \date 17/11/16
//! @param Personnage : un pointeur vers le personnge a inserer
//! \version 1.0
//!
//! Insere le personnage dans l'equipe courante
//!

void Equipe::ajouterPersonnage(Personnage *personnage)
{
    m_personnages.insert(personnage);
    mettreAChange();
    notifierTous();
}

//!
//! \brief Accesseur en lecture des personnages de l'equipe
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return la liste des personnages
//!
//! Retourne les personnages sous la forme d'un set
//!

std::set<Personnage *> Equipe::obtenirListePersonnage()
{
    return m_personnages;
}

//!
//! \brief Suppression d'un personnage d'une equipe
//! \author mleothaud
//! \date 17/11/16
//! @param personnage : pointeur vers le personnage a supprimer
//! \version 1.0
//!
//! Verification d'existence puis suppression du personnage
//!

void Equipe::supprimerPersonnage(Personnage *personnage)
{
    assert(m_personnages.find(personnage) != m_personnages.end());
    m_personnages.erase(m_personnages.find(personnage));
    mettreAChange();
    notifierTous();
}

//!
//! \brief Constructeur parametre de la classe equipe
//! \author mleothaud
//! \date 17/11/16
//! @param personnages : set de personnages a inserer dans l'equipe des sa creation
//! \version 1.0
//!
//! Insert tous les personnages du set place en parametre dans l'attribut personnages
//!

Equipe::Equipe(std::set<Personnage *> personnages)
{
    for (Personnage* p : personnages)
    {
        m_personnages.insert(p);
    }
}

//!
//! \brief Constructeur par defaut de l'equipe
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!

Equipe::Equipe()
{

}

//!
//! \brief Constructeur parametre de la classe equipe
//! \author mleothaud
//! \date 17/11/16
//! @param personnage : personnage à inserer dans le cas ou l'equipe n'est au depart constituee d'un seul personnage
//! \version 1.0
//!
//! Ajout du personnage a l'equipe
//!

Equipe::Equipe(Personnage *personnage)
{
    this->ajouterPersonnage(personnage);
}

//!
//! \brief Genere une equipe de zombies a affronter
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return l'equie de zombies generee
//!
//! genere l'equipe de zombies avec un nombre aleatoire pour chaque qui correspondra a sa puissance
//!

Equipe* Equipe::genererEquipeZombie()
{
    Equipe *e = new Equipe();
    for (int i=0;i<4;i++)
    {
        Zombie *z= new Zombie(rand()%4);
        e->ajouterPersonnage(z);
    }
    return e;
}

//!
//! \brief Serialise les données de l'équipe
//! \author nlesne
//! \date 12/11/17
//! \version 0.2
//! \return Chaine contenant les données de l'équipe
//!

std::string Equipe::serialiser() const
{
    std::string donnees_equipe = "<Equipe>";

    for (Personnage* p : m_personnages)
    {
        donnees_equipe += p->serialiser();
    }
    donnees_equipe += "</Equipe>";

    return donnees_equipe;
}

void Equipe::charger(std::string &donnees)
{
    if (!obtenirSousChaineEntre2Predicats(donnees, "<Equipe>","</Equipe>").empty())
    {
        while (!obtenirSousChaineEntre2Predicats(donnees,"<Humain>","</Humain>").empty())
        {
            Humain* h = new Humain();
            h->charger(obtenirSousChaineEntre2Predicats(donnees,"<Humain>","</Humain>"));
            this->ajouterPersonnage(h);
            supprimmerSousChaineEntre2Predicats(donnees,"<Humain>","</Humain>");
        }
    }
}

Equipe::~Equipe(){
    for(Personnage * p : m_personnages){
        delete p;
    }
}
