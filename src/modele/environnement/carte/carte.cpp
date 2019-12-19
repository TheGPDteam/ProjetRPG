#include "carte.h"

//! \file fichier campement
//! \date 17/11/16
//! \version 0.1


Carte::Carte(){
    //m_zones.push_back(Zone(64,64));
    //m_zoneActive = m_zones.front();
    for (int i = 0; i < 9; ++i){
       std::string zone = "./../rsc/carte/zone" + std::to_string(i+1) + ".txt";
       chargerZone(zone);
    }

    m_numZoneActive = 3;
    m_zoneActive = m_zones.at(m_numZoneActive);
}


//!
//! \brief Destructeur de la carte
//! \author nlesne
//! \date 14/10/17
//! \version 1.0
//!
Carte::~Carte(){
    for (int i = 0; i < m_zones.size(); ++i)
        delete m_zones.at(i);
}


//!
//! \brief Ajoute un observateur pour toutes les zones
//! \param obs
//! \author dolacoste
//!
void Carte::definirObservateurZones(Observateur &obs){
    for (int i = 0; i < m_zones.size(); ++i)
        m_zones.at(i)->ajouterObservateur(obs);
}


//!
//! \brief Accesseur en lecture de la zone active
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return la zone active de la carte
//!
Zone *Carte::obtenirZoneActive(){
    return m_zoneActive;
}


//!
//! \brief Fonction de chargement de la zone dont le nom du fichier est place en parametre
//! \param nomFichierZone : nom du fichier de chargement pour cette zone
//! \param x : abscisse dans la matrice pour cette zone
//! \param y : ordonnée dans la matrice pour cette zone
//! \version 0.2
//! \date 24/11/16
//! \author mleothaud
//!
void Carte::chargerZone(std::string nom_fichier_zone){
    std::ifstream fichier(nom_fichier_zone, std::ifstream::in);
    Zone * zone = new Zone(fichier);

    m_zones.push_back(zone);
    m_zoneActive = zone;

    mettreAChange();
    notifierTous();
}


//!
//! \brief Fonction de changement de la zone active de la carte
//! \param Direction : direction dans laquelle nous allons
//! \version 0.1
//! \date 02/06/17
//! \author mleothaud
//!

void Carte::changerZoneActive(int numeroZone){

    m_numZoneActive = numeroZone;
    m_zoneActive = m_zones.at(m_numZoneActive);

    mettreAChange();
    notifierTous();
}


//!
//! \brief Fonction de rechargement des objets dans les zones de la carte
//! \version 0.1
//! \date 01/03/18
//! \author mleothaud
//!
void Carte::recharger(){
    for (int i = 0; i < m_zones.size() ; ++i){
         m_zones.at(i)->recharger();
    }
}


//!
//! \brief Fonction pour retourner dans la zone où est le campement
//! \version 1.0
//! \date 09/03/18
//! \author mleothaud
//!
void Carte::zoneActiveCampement(){
   m_numZoneActive = 3;
   m_zoneActive = m_zones.at(m_numZoneActive);
}
