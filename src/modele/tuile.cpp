#include "tuile.h"

//! \file fichier tuile
//! \date 17/11/16
//! \version 1.0
//!


Tuile::Tuile(int val)
    :m_type{(TypeTuile)val}, m_jonction{TypeTuile::AucunType},m_extremiteCarte{false}
{
}

//!
//! \brief Accesseur en lecture de l'attribut estMarchable
//! \return si on peut marcher sur la tuile ou pas
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//!

bool Tuile::obtenirEstMarchable() const
{
    return (m_type == Herbe || m_type == Sable || m_type == Beton || m_type == Terre);
}


//!
//! \brief Accesseur en lecture de l'attribut peutApparaitre
//! \return si un objet ou un zombie peut apparaitre sur la case
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//!

bool Tuile::obtenirPeutApparaitre() const
{
    return obtenirEstMarchable();
}

//!
//! \brief Accesseur en lecture de l'attribut m_type
//! \return le type de la tuile
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//!

TypeTuile Tuile::obtenirType() const{
    return m_type;
}


void Tuile::definirExtremiteCarte(bool extremite)
{
    m_extremiteCarte = extremite;
}

bool Tuile::obtenirExtremiteCarte() const
{
    return m_extremiteCarte;
}


//!
//! \brief Accesseur en ecriture de l'attribut m_sous_type
//! \return le sous type de la tuile
//! \author rbourqui
//! \date 15/12/2017
//! \version 1.0
//!
void Tuile::definirHachageJonction(TypeTuile typeVoisin, TypeJonction positionVoisin)
{
    m_jonction = hacher(typeVoisin, positionVoisin);
}

//!
//! \brief Accesseur en lecture de l'attribut m_sous_type
//! \return le sous type de la tuile
//! \author rbourqui
//! \date 15/12/2017
//! \version 1.0
//!
int Tuile::obtenirHachageJonction() const{
    return m_jonction;
}

//!
//! \brief Fonction de hachage du type et de la position de jonction
//! \return le résultat du hachage
//! \author rbourqui
//! \date 20/12/2017
//! \version 1.0
//!
int Tuile::hacher(TypeTuile typeVoisin, TypeJonction positionVoisin){
    return typeVoisin * 100 + positionVoisin;
}
