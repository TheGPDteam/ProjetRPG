#include "inventaire.h"


//! \file fichier Inventaire
//! \date 17/11/16
//! \version 1.0

//!
//! \brief Constructeur par defaut
//! \author jsorin001
//! \date 03/10/16
//! \version 0.1
//!
//! Constructeur par defaut de l'objet Inventaire
//!

Inventaire::Inventaire()
{}

//!
//! \brief Destructeur par defaut
//! \author jsorin001
//! \date 03/10/16
//! \version 0.1
//!
//! Destructeur par defaut de l'objet Inventaire
//!

Inventaire::~Inventaire()
{
    for (Objet* o : m_objets)
    {
        delete o;
    }
}

//!
//! \brief Accesseur objets
//! \author jsorin001
//! \date 03/11/16
//! @return vecteur d'Objets avec la liste des Objets dans l'inventaire
//! \version 0.1
//!
//! Accesseur de la liste d'Objet de l'inventaire
//!

std::vector<Objet*> Inventaire::obtenirObjets() const
{
    return m_objets;
}

//!
//! \brief Accesseur taille max
//! \author jsorin001
//! \date 03/11/16
//! @return Entier contenant la taille maximale de l'inventaire
//! \version 0.1
//!
//! Accesseur de la taille maximal de l'inventaire
//!

unsigned short Inventaire::obtenirTailleMax() const
{
    return m_tailleMaximum;
}

//!
//! \brief Accesseur nombre objet
//! \author jsorin001
//! \date 03/11/16
//! @return Entier contenant le nombre d'Objets de l'inventaire
//! \version 0.1
//!
//! Accesseur de le nombre d'Objets contenus de l'inventaire
//!

unsigned short Inventaire::obtenirNombreObjet() const
{
    return m_objets.size();
}

//!
//! \brief Ajoute Objet
//! \author jsorin001
//! \date 03/11/16
//! \version 1.0
//!
//! Ajoute un Objet à l'inventaire
//!

void Inventaire::ajouterObjet(Objet *objet)
{
    if (!Inventaire::estPlein())
    {
        m_objets.push_back(objet);
    }
}

//!
//! \brief Supprime Objet
//! \author jsorin001, mleothaud
//! \date 03/11/16
//! \version 1.0
//!
//! Supprime un Objet de l'inventaire
//!

void Inventaire::supprimerObjet(Objet* objet)
{
    int i = 0;
    bool trouve= false;

    while (i <= this->obtenirNombreObjet() && !trouve)
    {
        if (objet == m_objets[i])
        {
            m_objets.erase(m_objets.begin() + i);
            trouve = true;
        }
        ++i;
    }
}

//!
//! \brief Donne l'état de l'inventaire
//! \author jsorin001
//! \date 03/11/16
//! @return vrai si l'inventaire est plein sinon faux
//! \version 1.0
//!
//! Vérifie si l'inventaire est plein
//!

bool Inventaire::estPlein() const
{
    return (obtenirNombreObjet() == this->obtenirTailleMax());
}

std::vector<std::string> Inventaire::serialiser() const
{
    std::vector<std::string> donnees_inventaire;
    std::vector<std::string> donnees_objets;
    std::vector<std::string> donnees_objet;

    for (Objet* obj : m_objets)
    {
        donnees_objet = obj->serialiser();
        donnees_objets.insert(donnees_objets.end(),donnees_objet.begin(),donnees_objet.end());
    }
    donnees_objets.insert(donnees_inventaire.end(),donnees_objets.begin(),donnees_objets.end());
    donnees_inventaire.push_back(std::to_string(m_tailleMaximum));

    return donnees_inventaire;
}
