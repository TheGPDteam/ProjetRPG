#include "vie.h"

//! \file fichier vie
//! \date 17/11/16
//! \version 1.0

//!
//! \brief Constructeur par défaut
//! \author jsorin001, mleothaud
//! \date 03/11/16
//! \version 0.1
//!
//! Constructeur par défaut de l'objet Vie
//!

Vie::Vie()
    :m_valeur{1},m_valeurMax{100}
{}

//!
//! \brief Constructeur paramétré
//! \author jsorin001, mleothaud
//! \date 03/11/16
//! @param valeurMax valeur maximale de la vie
//! \version 0.1
//!
//! Constructeur paramétré de l'objet Vie
//!

Vie::Vie(int valeurMax)
    :m_valeur{valeurMax},m_valeurMax{valeurMax}
{}

//!
//! \brief Accesseur valeur
//! \author jsorin001
//! \date 03/11/16
//! @return Entier valeur de la Vie
//! \version 1.0
//!
//! Accesseur de la valeur de la Vie
//!

int Vie::obtenirValeur() const
{
    return m_valeur;
}

//!
//! \brief Accesseur valeur max
//! \author jsorin001
//! \date 03/11/16
//! @return Entier valeur maximale de la Vie
//! \version 0.1
//!
//! Accesseur de la valeur maximale de la Vie
//!

int Vie::obtenirValeurMax() const
{
    return m_valeurMax;
}

//!
//! \brief Mutateur valeur
//! \author jsorin001
//! \date 03/11/16
//! \version 1.0
//!
//! Mutateur de la valeur de la Vie
//!

void Vie::definirValeur(int nouvelle_valeur)
{
    m_valeur = nouvelle_valeur;
}

//!
//! \brief Mutateur valeur max
//! \author jsorin001
//! \date 03/11/16
//! \version 1.0
//!
//! Mutateur de la valeur maximale de la Vie
//!

void Vie::definirValeurMax(int nouvelle_valeur_maximale)
{
    m_valeurMax = nouvelle_valeur_maximale;
}

//!
//! \brief diminiuer valeur
//! \author jsorin001
//! \date 03/11/16
//! @param valeur de la valeur à dimininuer
//! \version 1.0
//!
//! diminuer la valeur de la Vie
//!

void Vie::diminuer(int valeur)
{
    if (valeur > this->obtenirValeur())
        this->definirValeur(0);
    else
        this->definirValeur(this->obtenirValeur() - valeur);
}

//!
//! \brief augmenter valeur
//! \author jsorin001
//! \date 03/11/16
//! @param valeur de la valeur à augmenter
//! \version 1.0
//!
//! augmente la valeur de la Vie
//!

void Vie::augmenter(int valeur)
{
    if (this->obtenirValeur() + valeur > this->obtenirValeurMax())
        this->definirValeur(this->obtenirValeurMax());
    else
        this->definirValeur(this->obtenirValeur() + valeur);
}

//! \brief serialise les attributs de la classe Vie
//! \author Marius,nlesne
//! \date 19/10/17
//! \version 0.2
//!

std::string Vie::serialiser() const{
    return "<Vie>"
            "<Maximum>" + std::to_string(m_valeurMax) + "</Maximum>"
            "</Vie>";
}
//! \brief charge les attributs de la classe Vie
//! \author Marius
//! \date 19/10/17
//! \version 1.0
//!

void Vie::charger(const std::string &donnees){
    m_valeurMax = std::stoi(obtenirSousChaineEntre2Predicats(donnees,"<Maximum>","</Maximum>"));
    m_valeur = m_valeurMax;
}
