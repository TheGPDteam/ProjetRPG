#include "tuile.h"

//! \file fichier tuile
//! \date 17/11/16
//! \version 1.0
//!


Tuile::Tuile(int val)
    : m_directionChangementZone{Aucune}{

    m_numero = val - 1;

    if ((val > 13 && val < 18) || val == 33 || val == 34){
        m_type = Herbe;
    }

    m_type = (TypeTuile)(val%6);
    m_marchable = true/*archable && (m_type == Herbe || m_type == Sable || m_type == Beton || m_type == Terre)*/;

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
    return m_marchable;
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


int Tuile::obtenirNumero() const{
    return m_numero;
}


void Tuile::definirDirectionChangementZone(Direction dir)
{
    m_directionChangementZone = dir;
}

Direction Tuile::obtenirDirectionChangementZone() const{
    return m_directionChangementZone;
}
