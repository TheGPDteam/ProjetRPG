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
    assert(m_personnages.find(personnage)!=m_personnages.end());
    m_personnages.erase(m_personnages.find(personnage));
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
    m_personnages.insert(personnage);
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

std::vector<std::string> Equipe::serialiser() const
{
    std::vector<std::string> donnees_equipe;
    std::vector<std::string> donnees_personnages;
    for (Personnage* p : m_personnages )
    {
        std::vector<std::string> buffer = p->serialiser();
        donnees_personnages.insert(donnees_personnages.end(),buffer.begin(),buffer.end());
    }
    donnees_equipe.insert(donnees_equipe.end(),donnees_personnages.begin(),donnees_personnages.end());
}
