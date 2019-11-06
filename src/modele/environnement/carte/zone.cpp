#include "zone.h"
#include <utility>
#include <set>
#include <iostream>
#include <climits>
#include <sstream>

//! \file fichier zone
//! \date 17/11/16
//! \version 1.0

const int CASE_DIRECTION_OUEST = 6;
const int CASE_DIRECTION_SUD = 7;
const int CASE_DIRECTION_EST = 8;
const int CASE_DIRECTION_NORD = 9;


Zone::Zone(){
    init(64, 64);
}


//!
//! \brief Zone::Zone
//! \param longueur
//! \param largeur
//! \param fichier
//! \author dolacoste
//!
Zone::Zone(std::ifstream fichier){
    if (fichier.good()){
        init(fichier);
        definirNom("Zone " + (x * 3) + (y + 1));
    } else {
        init(64,64);
    }
}


void Zone::init(std::ifstream fichier){
    definirNom(valeurDe(fichier, "#nom"));

    std::vector<std::string> cases;
    std::string ligne;
    std::getline(fichier, ligne);
    while (!fichier.eof()){
        cases.push_back(ligne);
        std::getline(fichier,ligne);
    }

    fichier.close();

    for (unsigned int i = 0; i < fichier.size(); ++i){
        std::vector<int> valeursTuiles;
        ligne2Tuile(fichier, valeursTuiles, i);
        for (unsigned int j = 0; j < valeursTuiles.size(); ++j){
            Tuile * t = new Tuile(valeursTuiles[j]);
            if(true){

            }
            m_tuiles.insert(std::make_pair(t,std::make_pair(j,i)));
            m_position_to_tuile[std::make_pair(j,i)] = t;
        }
    }


    ajouterObjets(20);
}


std::string valeurDe(std::ifstream fichier, std::string valeur){
    std::string ligne;
    do{
        std::size_t pos = ligne.find(valeur);
        if (pos == std::string::npos){
            pos+= valeur.size() + 1;
            int debut = pos-1;
            while(valeur.substr())

        }

        std::getline(fichier,ligne);
    } while (!fichier.eof());

    return "error";
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


void ligne2Tuile(std::vector<std::string> fichier, std::vector<int> &tuiles, int i){
    int debutNumero = 0;
    int finNumero = 0;
    int numeroTuile = 0;
    // Le numero en entier sera concaténé dans la chaine de caractère
    std::string resultat = "";

    while(finNumero < fichier[i].size()){
        // Si la fin du numéro est rencontré
        if (fichier[i][finNumero] == ' '){
            debutNumero = finNumero + 1;
            finNumero = debutNumero + 1;

            // On transforme la chaine de caractère en  entier
            std::stringstream temp(resultat);
            temp >> numeroTuile;

            // Debug pour afficher le numéro des tuile lu
            //std::cout << numeroTuile << " ";

            tuiles.push_back(numeroTuile);
            resultat = "";

        // Sinon on continu de lire
        } else {
            // On ajoute le caratère du chiffre à la chaine de caractère du numéro courant
            resultat +=  fichier[i][finNumero];
            ++finNumero;
        }
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


int Zone::obtenirTaille() const {
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


    ajouterSols(Eau, MAX_TUILES_EAU_PER_ZONE, MAX_GROUPES_TUILES_EAU);
    ajouterSols(Sable, MAX_TUILES_SABLE_PER_ZONE, MAX_GROUPES_TUILES_SABLE);
    ajouterSols(Terre, MAX_TUILES_TERRE_PER_ZONE, MAX_GROUPES_TUILES_TERRE);

    ajouterObjets(20);
}


void Zone::ajouterSols(int type_sol, int max_type_sol, int max_groupe) {
    int nbGroupeTuileEau = rand() % max_groupe;

    for(int j = 0 ; j < nbGroupeTuileEau; ++j){
        int posX = rand() % m_largeur;
        int posY = rand() % m_hauteur;

        int nbTuiles = rand() % max_type_sol ;

        Tuile * t = m_position_to_tuile.at(std::make_pair(posX, posY));
        m_tuiles.erase(t);
        delete t;
        t = new Tuile((TypeTuile)type_sol);
        m_tuiles.insert(std::make_pair(t,std::make_pair(posX,posY)));
        m_position_to_tuile[std::make_pair(posX, posY)] = t;


        std::vector<std::pair<int, int> > positionsPossiblesVecteur;

        if (posX > 0) {
            positionsPossiblesVecteur.push_back({posX-1, posY});
        }

        if (posX+1 < m_largeur){
            positionsPossiblesVecteur.push_back({posX+1, posY});
        }

        if (posY > 0) {
            positionsPossiblesVecteur.push_back({posX, posY-1});
        }

        if (posY+1 < m_hauteur){
            positionsPossiblesVecteur.push_back({posX, posY+1});
        }

        for(int i = 0; i < nbTuiles; ++i){
            int pos = rand() % positionsPossiblesVecteur.size();
            std::pair<int, int> p = positionsPossiblesVecteur[pos];

            positionsPossiblesVecteur.erase(positionsPossiblesVecteur.begin() + pos);

            Tuile * t = m_position_to_tuile.at(std::make_pair(p.first, p.second));
            m_tuiles.erase(t);
            delete t;

            t = new Tuile(((TypeTuile)type_sol));
            m_tuiles.insert(std::make_pair(t,std::make_pair(p.first,p.second)));
            m_position_to_tuile[std::make_pair(p.first, p.second)] = t;

            if (p.first > 0){
                positionsPossiblesVecteur.push_back({p.first - 1, p.second});
            }

            if (p.first + 1 < m_largeur){
                positionsPossiblesVecteur.push_back({p.first + 1, p.second});
            }

            if (p.second > 0){
                positionsPossiblesVecteur.push_back({p.first, p.second - 1});
            }

            if (p.second + 1 < m_hauteur){
                positionsPossiblesVecteur.push_back({p.first, p.second + 1});
            }
        }
    }
}


void Zone::ajouterObjets(int nombre_objets){
    if (nombre_objets > 0) {
        for (int i = 0; i < nombre_objets; ++i) {
            int posX = DECALAGE_TUILE + (rand() % (m_largeur - 2 * DECALAGE_TUILE));
            int posY = DECALAGE_TUILE + (rand() % (m_hauteur - 2 * DECALAGE_TUILE));

            Tuile * t  = m_position_to_tuile.at(std::make_pair(posX,posY));

            // Permet de verifier que la tuile puisse contenir des objets & qu'il n'y a pas d'objet deja present
            while (!t->obtenirPeutApparaitre() && !objetPresent(std::make_pair(posX,posY))) {
                posX = DECALAGE_TUILE + rand() % (m_largeur - 2 * DECALAGE_TUILE);
                posY = DECALAGE_TUILE + rand() % (m_hauteur - 2 * DECALAGE_TUILE);
                t = m_position_to_tuile.at(std::make_pair(posX,posY));
            }

            //int typeObj = rand()%5; //A revoir si un jour integration objets autres que arme et vivre
            int typeObj = rand()%6;
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
                    m_objets.insert(std::make_pair(new PartieBus() ,std::make_pair(posX,posY)));
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
