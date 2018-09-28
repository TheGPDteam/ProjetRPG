 #include "carte.h"

//! \file fichier campement
//! \date 17/11/16
//! \version 0.1


Carte::Carte(){
    //m_zones.push_back(Zone(64,64));
    //m_zoneActive = m_zones.front();
    for (int i=0;i<3;++i)
    {
        for (int j=0; j<3;++j)
        {
            std::string zone = "./../rsc/carte/zone" + std::to_string(i*3 + j) + ".txt";
            chargerZone(zone,i,j);
        }
    }
    m_xZoneActive = m_yZoneActive = 1;
    m_zoneActive = m_zones[m_xZoneActive][m_yZoneActive];
}

//!
//! \brief Destructeur de la carte
//! \author nlesne
//! \date 14/10/17
//! \version 1.0
//!

Carte::~Carte()
{
    for (int x = 0; x < TAILLE_CARTE_X;x++)
        for (int y = 0; y < TAILLE_CARTE_Y; y++)
            delete m_zones[x][y];
}

//!
//! \brief Accesseur en lecture de la zone active
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return la zone active de la carte
//!

Zone *Carte::obtenirZoneActive()
{
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

void Carte::chargerZone(std::string nomFichierZone, short x, short y)
{
    std::vector<std::string> cases;
    std::ifstream fichier(nomFichierZone, std::ifstream::in);
    if (fichier.good())
    {
        std::string ligne;
        std::getline(fichier,ligne);
        while(!fichier.eof())
        {
            cases.push_back(ligne);
            std::getline(fichier,ligne);
        }
        fichier.close();
        Zone* zone = new Zone(cases.size(),cases.size(),cases);
        /*m_zones.push_back(zone);
        m_zoneActive = m_zones.front();*/
        m_zones[x][y] = zone;
        m_zoneActive = m_zones[x][y];
    }
    else
    {
        /*m_zones.push_back(Zone(64,64));
        m_zoneActive = m_zones.front();*/
        m_zones[x][y] = new Zone(64,64);
        m_zoneActive = m_zones[x][y];
    }
}

//!
//! \brief Fonction de changement de la zone active de la carte
//! \param Direction : direction dans laquelle nous allons
//! \version 0.1
//! \date 02/06/17
//! \author mleothaud
//!

void Carte::changerZoneActive(Direction direction)
{
    switch (direction) {
    case Nord :
    {
        m_yZoneActive -= 1;
        m_zoneActive = m_zones[m_xZoneActive][m_yZoneActive];
        break;
    }
    case Sud :
    {
        m_yZoneActive += 1;
        m_zoneActive = m_zones[m_xZoneActive][m_yZoneActive];
        break;
    }
    case Est :
    {
        m_xZoneActive += 1;
        m_zoneActive = m_zones[m_xZoneActive][m_yZoneActive];
        break;
    }
    case Ouest :
    {
        m_xZoneActive -= 1;
        m_zoneActive = m_zones[m_xZoneActive][m_yZoneActive];
        break;
    }
    case Aucune :
    {
        break;
    }
    }
}

//!
//! \brief Fonction de rechargement des objets dans les zones de la carte
//! \version 0.1
//! \date 01/03/18
//! \author mleothaud
//!

void Carte::recharger()
{
    for (int i = 0; i < TAILLE_CARTE_X ; i++)
    {
        for(int j = 0; j < TAILLE_CARTE_Y ; ++j)
        {
            m_zones[i][j]->recharger();
        }
    }
}

//!
//! \brief Fonction pour retourner dans la zone ou est le campement
//! \version 1.0
//! \date 09/03/18
//! \author mleothaud
//!

void Carte::zoneActiveCampement()
{
   m_xZoneActive = 1;
   m_yZoneActive = 1;
   m_zoneActive = m_zones[m_xZoneActive][m_yZoneActive];
}
