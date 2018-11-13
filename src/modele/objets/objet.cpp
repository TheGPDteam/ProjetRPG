#include "objet.h"

//! \file fichier objet
//! \date 17/11/16
//! \version 1.0


//!
//! \brief Constructeur par défaut
//! \author nlesne
//! \date 18/01/18
//! \version 1.0
//!

Objet::Objet()
{

}

//!
//! \brief Constructeur paramétré
//! \author jsorin001
//! \date 03/11/16
//! \version 0.1
//!
//! Constructeur paramétré
//!

Objet::Objet(std::string nom, std::string description)
    : m_nom{nom},
      m_description{description}
{

}

//!
//! \brief Destructeur par defaut
//! \author jsorin001
//! \date 03/11/16
//! @return Entier contenant la taille maximale de l'inventaire
//! \version 0.1
//!
//! Destructeur par défaut de l'objet Objet
//!

Objet::~Objet()
{

}

//!
//! \brief Accesseur nom
//! \author jsorin001
//! \date 03/11/16
//! @return nom de l'Objet
//! \version 1.0
//!
//! Accesseur du nom de l'Objet
//!

std::string Objet::obtenirNom() const
{
    return m_nom;
}

//!
//! \brief Accesseur description
//! \author jsorin001
//! \date 03/11/16
//! @return la description de l'Objet
//! \version 1.0
//!
//! Accesseur de la description de l'Objet
//!

std::string Objet::obtenirDescription() const
{
    return m_description;
}

//!
//! \brief Mutateur description
//! \author jsorin001
//! \date 03/11/16
//! \version 1.0
//!
//! Mutateur de la description de l'Objet
//!

void Objet::definirDescription(const std::string &nom)
{
    m_description = nom;
}

//!
//! \brief Mutateur nom
//! \author jsorin001
//! \date 03/11/16
//! \version 1.0
//!
//! Mutateur du nom de l'Objet
//!

void Objet::definirNom(const std::string &nom)
{
    m_nom = nom;
}

std::string Objet::serialiser() const
{
    return "<Objet>"
            "   <Nom>" + m_nom + "</Nom>"
            "   <Description>" + m_description + "</Description>"
            "</Objet>";

}

TypeObjet Objet::obtenirType() const {
    return TypeObjet::Objet;
}

void Objet::charger(const std::string &donnees)
{

}

//!
//! \brief Comparateur d'égalité
//! \author nlesne
//! \date 12/11/18
//! \param obj un pointeur sur un objet
//! \return Vrai si les objets sont égaux
//! \version 1.0
//!
bool Objet::operator==(const Objet *obj)
{
    if (obj == nullptr || m_nom != obj->obtenirNom() || m_description != obj->obtenirDescription())
        return false;
    return true;
}

//!
//! \brief Comparateur d'
//! \author nlesne
//! \date 12/11/18
//! \param obj un pointeur sur un objet
//! \return Vrai si this est
//! \version 1.0
//!
bool Objet::operator>(const Objet *obj)
{
    if (obj == nullptr)
        return false;
    return m_nom > obj->obtenirNom();
}
