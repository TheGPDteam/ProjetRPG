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
    mettreAChange();
    notifierTous();
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
    mettreAChange();
    notifierTous();
}


//!
//! \brief Vide l'inventaire
//! \author nlesne
//! \date 22/10/18
//! \version 1.0
//!
//! Supprime tous les objets de l'inventaire
//!
void Inventaire::viderInventaire()
{
    if (!m_objets.empty())
    {
        for (Objet* o : m_objets)
        {
            this->supprimerObjet(o);
        }
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

//!
//! \brief Serialise les objets de l'inventaire
//! \author nlesne
//! \date 12/11/17
//! \return Chaine contenant l'inventaire sous format XML
//! \version 0.1
//!
//! Convertit les données des objets de l'inventaire au format XML
//!

std::string Inventaire::serialiser() const
{
    std::string donnees_objets = "<Inventaire>";
    for (Objet* obj : m_objets)
        donnees_objets += obj->serialiser();
    donnees_objets += "</Inventaire>";

    return donnees_objets;
}

void Inventaire::charger(const std::string &donnees)
{
    std::string donneesInventaire = donnees;
    if (donneesInventaire.find("<Arme>") != std::string::npos)
    {
        while (!obtenirSousChaineEntre2Predicats(donneesInventaire,"<Arme>","</Arme>").empty())
        {
            Arme* a = new Arme();
            a->charger(obtenirSousChaineEntre2Predicats(donneesInventaire,"<Arme>","</Arme>"));
            m_objets.push_back(a);
            supprimmerSousChaineEntre2Predicats(donneesInventaire,"<Arme>","</Arme>");
        }
    }

    if (donneesInventaire.find("<Vivre>") != std::string::npos)
    {
        while (!obtenirSousChaineEntre2Predicats(donneesInventaire,"<Vivre>","</Vivre>").empty())
        {
            Vivre* v = new Vivre();
            v->charger(obtenirSousChaineEntre2Predicats(donneesInventaire,"<Vivre>","</Vivre>"));
            m_objets.push_back(v);
            supprimmerSousChaineEntre2Predicats(donneesInventaire,"<Vivre>","</Vivre>");
        }
    }

    if (donneesInventaire.find("<Objet>") != std::string::npos)
    {
        while (!obtenirSousChaineEntre2Predicats(donneesInventaire,"<Objet>","</Objet>").empty())
        {
            Objet* obj = new Objet();
            obj->charger(obtenirSousChaineEntre2Predicats(donneesInventaire,"<Vivre>","</Vivre>"));
            m_objets.push_back(obj);
            supprimmerSousChaineEntre2Predicats(donneesInventaire,"<Objet>","</Objet>");
        }
    }

    mettreAChange();
    notifierTous();

}
