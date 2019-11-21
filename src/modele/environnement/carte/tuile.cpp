#include "tuile.h"

//! \file fichier tuile
//! \date 17/11/16
//! \version 1.0
//!


Tuile::Tuile(int val)
    : m_directionChangementZone{Aucune}{

    m_numero = val - 1;

    // Definition de la categorie de la tuile
    if (m_numero == 0 || m_numero == 3 ||
        (m_numero >= 16 && m_numero % 16 >= 8 && m_numero % 16 <= 12) ||
            m_numero >= 16 * 4){
        m_categorie = NonTerreux;
    } else if (m_numero == 1 || m_numero == 4 ||
               (m_numero >= 16 && m_numero < 16 * 4 && m_numero % 16 >= 12)){
        m_categorie = Terreux;
    } else if (m_numero >= 16 && m_numero < 4 * 16 && m_numero % 16 <= 7){
        m_categorie = EauTerreux;
    } else if (m_numero == 2){
        m_categorie = Aqueux;
    } else if (m_numero == 5){
        m_categorie = ObstacleNonOrganique;
    } else if (m_numero == 6 || m_numero == 7){
        m_categorie = ObstacleOrganique;
    } else if (m_numero >= 8 && m_numero <= 12){
        m_categorie = Sortie;
    }

    // Definition du type de la tuile
    if (m_numero == 0){
        m_type = Sable;
    } else if (m_numero == 1){
        m_type = Herbe;
    } else if (m_numero == 2){
        m_type = Eau;
    } else if (m_numero == 3){
        m_type = Goudron;
    } else if (m_numero == 4){
        m_type = Terre;
    } else if (m_numero >= 5 && m_numero <= 8){
        m_type = Obstacle;
    } else if (m_numero == 9){
        m_type = SortieDroite;
    } else if (m_numero == 10){
        m_type = SortieGauche;
    } else if (m_numero == 11){
        m_type = SortieHaut;
    } else if (m_numero == 13){
        m_type = SortieBas;
    } else if (m_numero >= 14 && m_numero <= 18){
        m_type = HerbeDecoration;
    } else if (m_numero >= 19){
        m_type = Jointure;
    }

    m_marchable = (m_categorie == NonTerreux || m_categorie == Terreux
                   || m_categorie == Sortie || m_categorie == EauTerreux);
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
