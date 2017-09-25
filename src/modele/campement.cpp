#include "campement.h"

//! \file fichier campement
//! \date 17/11/16
//! \version 1.0

//!
//! \brief Constructeur par defaut de l'objet campement
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
//! Construit un objet de la classe campement en initialisant la quantite de vivres à 0
//!

Campement::Campement()
    :m_quantiteVivre{0}
{
}

//!
//! \brief Ajout d'un vivre au campement
//! \author mleothaud
//! \date 17/11/16
//! @param vivre : un vivre qui sera ajoute au stock des vivres
//! \version 1.0
//!
//! Ajout d'un vivre au stock du campement
//!

void Campement::ajouterVivre(Vivre vivre)
{
    Vivre *vivreBis = new Vivre(vivre);
    m_stockVivre.insert(m_stockVivre.begin(), vivreBis);
    m_quantiteVivre++;
}

//!
//! \brief Permet d'obtenir le nombre de vivres dans le campement
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return le nombre de vivres du campement
//!

unsigned short Campement::obtenirNbVivres() const
{
    return m_quantiteVivre;
}

//!
//! \brief Permet de consommer un Vivre
//! \author mleothaud
//! \date 17/11/16
//! @param nbVivresConsommes : Nombre de vivres que l'on doit consommer
//! \version 1.0
//!
//! Enleve les vivres du stock et decremente la quantite enregistree
//!

void Campement::consommerVivre(unsigned short nbVivresConsommes)
{
    for (int i=0; i<nbVivresConsommes;i++)
    {
        m_quantiteVivre--;
        m_stockVivre.erase(m_stockVivre.begin());
    }
}

//!
//! \brief Permet d'ajouter une personne au campement et de l'integrer a une equipe
//! \author mleothaud
//! \date 17/11/16
//! @param perso : Personnage à integrer
//! @param equipe : Equipe dans laquelle integrer le personnage
//! \version 1.0
//!
//! Ajoute le personnage à l'equipe desiree
//!

void Campement::ajouterPersonne(Personnage* perso, Equipe *equipe)
{
    equipe->ajouterPersonnage(perso);
}

//!
//! \brief Accesseur en lecture de l'equipe de chasse
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return l'equipe de chasse
//!

Equipe* Campement::obtenirChasse()
{
    return &m_equipeChasse;
}

//!
//! \brief Accesseur en lecture de l'equipe de recolte
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return l'equipe de recolte
//!

Equipe* Campement::obtenirRecolte()
{
    return &m_equipeRecolte;
}
