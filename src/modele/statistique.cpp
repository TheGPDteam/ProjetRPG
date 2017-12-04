#include "statistique.h"

//! \file fichier statistique
//! \date 17/11/16
//! \version 0.1

//!
//! \brief Constructeur par defaut
//! \date 10/11/16
//! \author mleothaud
//! \version 1.0
//!
//! Constructeur par defaut de la classe statistique
//!

Statistique::Statistique()
    :m_statActuelle{(rand()%m_STATMAX) +1}
{}

//!
//! \brief Accesseur en lecture de la valeur de la statatistique
//! \date 10/11/16
//! \author mleothaud
//! \version 1.0
//!

int Statistique::obtenirValeur() const
{
    return m_statActuelle;
}

//!
//! \brief Accesseur en lecture de la valeur maximum des statistiques
//! \date 10/11/16
//! \author mleothaud
//! \version 1.0
//!

int Statistique::obtenirValeurMax() const
{
    return m_STATMAX;
}

//!
//! \brief Accesseur en ecriture de la valeur de la statistique
//! \date 10/11/16
//! \author mleothaud
//! @param nom string Nom de la quête
//! \version 1.0
//!
//! On verifie que la valeur a affecter est bien inferieure ou egale a la valeur max
//! On l'affecte si oui, on affecte la valeur max sinon
//!

void Statistique::definirValeur(int valeur)
{
    if (valeur <= m_STATMAX)
        m_statActuelle=valeur;
    else
        valeur=rand()%m_STATMAX+1;
}

//!
//! \brief Permet d'augmenter la valeur d'une statistique
//! \date 10/11/16
//! \author mleothaud
//! @param valeur : valeur a augmenter
//! \version 1.0
//!
//! Verifie que si on incremente la statistique de la valeur, elle est comprise entre 1 et 20
//! Si oui incremente la statistique de la valeur, si non on cherche a savoir si la valeur aurait ete superieure
//! a 20, auquel cas on affecte 0 a la stat, ou inferieur a 0 auquel cas on affecte 1
//!

void Statistique::augmenter(int valeur)
{
    if ((valeur+m_statActuelle) <= m_STATMAX && (valeur+m_statActuelle) >  0)
        m_statActuelle+=valeur;
    else if (valeur<0)
        m_statActuelle=1;
    else if (valeur>0)
        m_statActuelle=20;
}

//! \brief serialise les attributs de la classe Statistique
//! \author parMarius,nlesne
//! \date 19/10/17
//! \version 0.2
//!


std::string Statistique::serialiser() const{
    return "<Statistique>\n"
            "   <Actuelle>\n" + std::to_string(m_statActuelle) + "\n</Actuelle>\n"
            "   <Maximum>\n" + std::to_string(m_STATMAX) + "\n</Maximum>\n"
            "</Statistique>\n";
}

//! \brief charge les attribut de la classe Statistique
//! \author parMarius
//! \date 19/10/17
//! \version 1.0
//!

void Statistique::charger(std::vector<std::string> donnees){
    m_statActuelle = std::stoi(donnees[0]);
}
