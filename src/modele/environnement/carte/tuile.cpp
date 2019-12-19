#include "tuile.h"

//! \file fichier tuile
//! \date 17/11/16
//! \version 1.0
//!


Tuile::Tuile(int num_sol)
    : m_directionChangementZone{Aucune}{

    m_numSol = num_sol - 1;
    m_numDeco = -1;
    m_marchable = true;
    mettreAJourMarcheable(m_numSol);
}


void Tuile::definirDecoration(int num_decoration){
    m_numDeco = num_decoration-1;
    mettreAJourMarcheable(m_numDeco);
}


bool Tuile::estDecoree() const {
    return m_numDeco != -1;
}

void Tuile::mettreAJourMarcheable(int numero){
    if (numero == -1) return;

    // Definition de la categorie de la tuile
    if (numero == 0 || numero == 3 ||
        (numero >= 16 && numero % 16 >= 8 && numero % 16 <= 12) ||
            numero >= 16 * 4){
        m_categorie = NonTerreux;
    } else if (numero == 1 || numero == 4 ||
               (numero >= 16 && numero < 16 * 4 && numero % 16 >= 12)){
        m_categorie = Terreux;
    } else if (numero >= 16 && numero < 4 * 16 && numero % 16 <= 7){
        m_categorie = EauTerreux;
    } else if (numero == 2){
        m_categorie = Aqueux;
    } else if (numero == 5){
        m_categorie = ObstacleNonOrganique;
    } else if (numero == 6 || numero == 7){
        m_categorie = ObstacleOrganique;
    } else if (numero >= 8 && numero <= 12){
        m_categorie = Sortie;
    }

    // Definition du type de la tuile
    if (numero == 0){
        m_type = Sable;
    } else if (numero == 1){
        m_type = Herbe;
    } else if (numero == 2){
        m_type = Eau;
    } else if (numero == 3){
        m_type = Goudron;
    } else if (numero == 4){
        m_type = Terre;
    } else if (numero >= 5 && numero <= 8){
        m_type = Obstacle;
    } else if (numero == 9){
        m_type = SortieDroite;
    } else if (numero == 10){
        m_type = SortieGauche;
    } else if (numero == 11){
        m_type = SortieHaut;
    } else if (numero == 13){
        m_type = SortieBas;
    } else if (numero >= 14 && numero <= 18){
        m_type = HerbeDecoration;
    } else if (numero >= 19){
        m_type = Jointure;
    }

    m_marchable = (m_categorie == NonTerreux || m_categorie == Terreux
                   || m_categorie == Sortie || m_categorie == EauTerreux) && m_marchable;
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


int Tuile::obtenirSol() const{
    return m_numSol;
}

int Tuile::obtenirDecoration() const{
    return m_numDeco;
}



void Tuile::definirDirectionChangementZone(Direction dir)
{
    m_directionChangementZone = dir;
}

Direction Tuile::obtenirDirectionChangementZone() const{
    return m_directionChangementZone;
}
