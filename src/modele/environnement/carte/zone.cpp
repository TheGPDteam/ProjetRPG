#include "zone.h"
#include <utility>
#include <set>
#include <iostream>
#include <climits>
#include <assert.h>
#include <sstream>

//! \file fichier zone
//! \date 17/11/16
//! \version 1.0

const int CASE_DIRECTION_OUEST = 6;
const int CASE_DIRECTION_SUD = 7;
const int CASE_DIRECTION_EST = 8;
const int CASE_DIRECTION_NORD = 9;


Zone::Zone(int largeur, int hauteur){
    init(largeur, hauteur);
}


//!
//! \brief Zone::Zone
//! \param longueur
//! \param largeur
//! \param fichier
//! \author dolacoste
//!
Zone::Zone(std::ifstream &fichier){
    if (fichier.good())  init(fichier);
    else                 init(64,64);
}


void Zone::init(std::ifstream & fichier){
    std::string ligne;
    std::getline(fichier, ligne);
    assert(!fichier.eof());

    std::vector<std::string> valeurs;

    // Nom
    decouper(ligne, valeurs, " ");
    assert(valeurs.size() == 2);
    definirNom(valeurs[1]);


    // Dimensions
    std::getline(fichier, ligne);
    assert(!fichier.eof());
    decouper(ligne, valeurs, " ");

    assert(valeurs.size() == 3);


    m_largeur = stoi(valeurs[1]);
    m_hauteur = stoi(valeurs[2]);

    // Lecture de #sol
    std::getline(fichier, ligne);
    assert(!fichier.eof());

    // Lecture numéros
    for(int i = 0; i < m_hauteur; ++i){
        std::getline(fichier,ligne);
        std::vector<std::string> valeurs;
        decouper(ligne, valeurs, " ");
        assert(valeurs.size() == m_largeur);
        for (unsigned int j = 0; j < m_largeur; ++j){
            Tuile * t = new Tuile(stoi(valeurs[j]));
            m_tuiles.insert(std::make_pair(t,std::make_pair(j,i)));
            m_position_to_tuile[std::make_pair(j,i)] = t;
        }
    }


    // Lecture de #decoration
    std::getline(fichier, ligne);
    assert(!fichier.eof());

    // Lecture numéros
    for(int i = 0; i < m_hauteur; ++i){
        std::getline(fichier, ligne);
        std::vector<std::string> valeurs;
        decouper(ligne, valeurs, " ");
        assert(valeurs.size() == m_largeur);
        for (unsigned int j = 0; j < m_largeur; ++j){
            m_position_to_tuile.at(std::make_pair(j,i))->definirDecoration(stoi(valeurs[j]));
        }
    }

    // Lecture des points de téléportations
    while(!fichier.eof()){
        std::getline(fichier, ligne);
        std::vector<std::string> valeurs;
        decouper(ligne, valeurs, " ");

        if (valeurs.size() == 8){
            int pos1X = stoi(valeurs[1]);
            int pos1Y = stoi(valeurs[2]);
            int pos2X = stoi(valeurs[3]);
            int pos2Y = stoi(valeurs[4]);
            int dir = stoi(valeurs[5]);
            int arriveX = stoi(valeurs[6]);
            int arriveY = stoi(valeurs[7]);

            m_zonesChangement.push_back(ZoneChangementZone(pos1X, pos1Y, pos2X, pos2Y, (Direction)dir, arriveX, arriveY));
        }
    }

    fichier.close();
    ajouterObjets(20);
}

void Zone::init(int largeur, int hauteur){
     m_largeur = largeur;
     m_hauteur = hauteur;
}


Zone::~Zone(){
    // Libération du dictionnaire d'objets
    for (auto &it : m_objets){
        delete it.first;
    }

    // Libération des tuiles de la zone
    for (auto &it : m_tuiles){
        delete it.first;
    }
}


Tuile* Zone::obtenirTuile(int x, int y) const {
    std::pair<int,int> position;
    position.first=x;
    position.second=y;
    for (auto it = m_tuiles.begin(); it != m_tuiles.end(); ++it )
        if (it->second == position)
            return it->first;
    return nullptr;
}


Tuile* Zone::obtenirTuile(std::pair <int,int> position) const {
    for (auto it = m_tuiles.begin(); it != m_tuiles.end(); ++it )
        if (it->second == position)
            return it->first;
    return nullptr;
}


ZoneChangementZone* Zone::obtenirChangement(Joueur * joueur){
    for (int i = 0; i < m_zonesChangement.size(); ++i){
        if (m_zonesChangement.at(i).estSur(joueur)){
            return &m_zonesChangement.at(i);
        }
    }

    return nullptr;
}


//!
//! \brief Zone::obtenirObjet
//! \param position
//! \return l'objet a cette position ou nullptr s'il n'y en a pas
//!
Objet* Zone::obtenirObjet(std::pair <int,int> position) const {
    for (auto it = m_objets.begin(); it != m_objets.end(); ++it)
        if (it->second == position)
            return it->first;
    return nullptr;
}


bool Zone::objetPresent(std::pair<int, int> position) const {
    return obtenirObjet(position) != nullptr;
}


void Zone::supprimerObjet(Objet* obj) {
    m_objets.erase(m_objets.find(obj));
    mettreAChange();
    notifierTous();
}


std::map <Objet*,std::pair <int,int>> Zone::obtenirObjets() const {
    return m_objets;
}


std::string Zone::obtenirNom()
{
    return m_nom;
}


void Zone::definirNom(std::string nom){
    m_nom = nom;
}


std::map<Tuile *, std::pair<int, int> > Zone::obtenirTuiles() const {
    return m_tuiles;
}


int Zone::obtenirLargeur() const {
    return m_largeur;
}


int Zone::obtenirHauteur() const {
    return m_largeur;
}


void Zone::initZone() {
    for(int i = 0; i < m_hauteur; ++i){
        for(int j = 0; j < m_largeur; ++j){
            Tuile * t = new Tuile((TypeTuile)2);
            m_tuiles.insert(std::make_pair(t,std::make_pair(i,j)));
            m_position_to_tuile[std::make_pair(i,j)] = t;
        }
    }

    m_objets.insert(std::make_pair(new Objet{"Oreille de zombie", "Ouloulou, probablement tombée par hasard d'un zombie, vous devriez courir.", 0, 640}, std::make_pair(42,42)));
    ajouterObjets(20);
}

void Zone::ajouterObjets(int nombre_objets){
    if (nombre_objets > 0) {
        for (int i = 0; i < nombre_objets; ++i) {
            int posX = DECALAGE_TUILE + (rand() % (m_largeur - 2 * DECALAGE_TUILE));
            int posY = DECALAGE_TUILE + (rand() % (m_hauteur - 2 * DECALAGE_TUILE));

            Tuile * t  = m_position_to_tuile.at(std::make_pair(posX, posY));

            // Permet de verifier que la tuile puisse contenir des objets & qu'il n'y a pas d'objet deja present
            while (!t->obtenirPeutApparaitre() && !objetPresent(std::make_pair(posX, posY))) {
                posX = DECALAGE_TUILE + rand() % (m_largeur - 2 * DECALAGE_TUILE);
                posY = DECALAGE_TUILE + rand() % (m_hauteur - 2 * DECALAGE_TUILE);
                t = m_position_to_tuile.at(std::make_pair(posX, posY));
            }

            //int typeObj = rand()%5; //A revoir si un jour integration objets autres que arme et vivre
            int typeObj = rand() % 6;
            switch (typeObj) {
            case 0:
                m_objets.insert(std::make_pair(new Vivre(),std::make_pair(posX,posY)));
                break;
            case 1:
                m_objets.insert(std::make_pair(new Vivre(),std::make_pair(posX,posY)));
                break;
            case 2:
                m_objets.insert(std::make_pair(new Arme() ,std::make_pair(posX,posY)));
                break;
            case 3:
                m_objets.insert(std::make_pair(new Arme() ,std::make_pair(posX,posY)));
                break;
            /*case 4://A revoir pour un objet aléatoire
                m_objets.insert(std::make_pair(new Objet("Montre du temps","Permet de garder un oeil sur le temps"),std::make_pair(posX,posY)));
                break;*/
            case 5:
                m_objets.insert(std::make_pair(new ObjetQuetePrincipale() ,std::make_pair(posX,posY)));
                break;
            default:
                break;
            }
        }
    }

    mettreAChange();
    notifierTous();
}


void Zone::initialiserSousTypeTuile(){

}

//!
//! \brief Fonction de rechargement de la zone
//! \version 0.1
//! \date 01/03/18
//! \author mleothaud
//!


void Zone::recharger(){
    ajouterObjets(20 - m_objets.size());
}
