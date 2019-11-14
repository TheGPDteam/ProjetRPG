#include "zone.h"
#include <utility>
#include <set>
#include <iostream>
#include <climits>

//! \file fichier zone
//! \date 17/11/16
//! \version 1.0

const int CASE_DIRECTION_OUEST = 6;
const int CASE_DIRECTION_SUD = 7;
const int CASE_DIRECTION_EST = 8;
const int CASE_DIRECTION_NORD = 9;

Zone::Zone(int longueur, int largeur)
    : m_largeur{largeur},
      m_hauteur{longueur}
{
    initZone();
}

void ligne2Tuile(std::vector<std::string> fichier, std::vector<int> &tuiles, int i)
{

    for (unsigned int j = 0; /*j < (unsigned int) 129 &&*/ j < fichier[i].size(); ++j)
    {
        int cpt=0;
        if(fichier[i][j]==' ')
        {
            ++cpt;
        }
        else
        {
            int type;
            type = (int) fichier[i][j] - '0';
            tuiles.push_back(type);
        }
    }

}

//!
//! \brief Zone::Zone
//! \param longueur
//! \param largeur
//! \param fichier
//! \author dolacoste
//!
Zone::Zone(int longueur, int largeur, std::vector<std::string> fichier)
    : m_largeur{largeur},
      m_hauteur{longueur}
{
    for (unsigned int i = 0; i < fichier.size(); ++i){
        std::vector<int> valeursTuiles;
        ligne2Tuile(fichier, valeursTuiles, i);
        for (unsigned int j = 0; j < valeursTuiles.size(); ++j){
            if (valeursTuiles[j] < 6) {

                Tuile * t = new Tuile((TypeTuile)valeursTuiles[j], (i>=DECALAGE_TUILE && j >= DECALAGE_TUILE) && (i < fichier.size()-DECALAGE_TUILE && j < valeursTuiles.size()- DECALAGE_TUILE));
                m_tuiles.insert(std::make_pair(t,std::make_pair(j,i)));
                m_position_to_tuile[std::make_pair(j,i)] = t;
            } else {

                Tuile* t = new Tuile(Beton);
                switch (valeursTuiles[j]) {
                case CASE_DIRECTION_OUEST:
                    t->definirDirectionChangementZone(Ouest);
                    break;
                case CASE_DIRECTION_SUD:
                    t->definirDirectionChangementZone(Sud);
                    break;
                case CASE_DIRECTION_EST:
                    t->definirDirectionChangementZone(Est);
                    break;
                case CASE_DIRECTION_NORD:
                    t->definirDirectionChangementZone(Nord);
                default:
                    break;
                }

                m_tuiles.insert(std::make_pair(t,std::make_pair(j,i)));
                m_position_to_tuile[std::make_pair(j,i)] = t;
            }

        }
    }
    ajouterObjets(20);
    initialiserSousTypeTuile();
}

Zone::~Zone(){
    // Libération du dictionnaire d'objets
    for (auto &it : m_objets)
    {
        delete it.first;
    }

    // Libération des tuiles de la zone
    for (auto &it : m_tuiles)
    {
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

std::map<Tuile *, std::pair<int, int> > Zone::obtenirTuiles() const {
    return m_tuiles;
}

int Zone::obtenirTaille() const {
    return m_largeur;
}

void Zone::initZone() {
    for(int i = 0; i < m_hauteur; i++)
    {
        for(int j = 0; j < m_largeur; j++)
        {
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

        if(posX > 0) {
            positionsPossiblesVecteur.push_back({posX-1, posY});
        }

        if(posX+1 < m_largeur){
            positionsPossiblesVecteur.push_back({posX+1, posY});
        }

        if(posY > 0) {
            positionsPossiblesVecteur.push_back({posX, posY-1});
        }

        if(posY+1 < m_hauteur){
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

            if(p.first > 0){
                positionsPossiblesVecteur.push_back({p.first-1, p.second});
            }

            if(p.first+1 < m_largeur){
                positionsPossiblesVecteur.push_back({p.first+1, p.second});
            }

            if(p.second > 0){
                positionsPossiblesVecteur.push_back({p.first, p.second-1});
            }

            if(p.second + 1 < m_hauteur){
                positionsPossiblesVecteur.push_back({p.first, p.second+1});
            }
        }
    }
}

void Zone::ajouterObjets(int nombre_objets)
{
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
    for(auto p : m_position_to_tuile){
        Tuile *t = p.second;
        if(t->obtenirType() == TypeTuile::Eau || t->obtenirType() == TypeTuile::Arbre) {
            t->definirHachageJonction(TypeTuile::AucunType, TypeJonction::AucuneJonction);
            continue;
        }
        std::set<TypeTuile> compatible;
        if(t->obtenirType() == TypeTuile::Herbe){
            compatible.insert(TypeTuile::Eau);
            compatible.insert(TypeTuile::Arbre);
            compatible.insert(TypeTuile::Sable);
        }else if(t->obtenirType() == TypeTuile::Sable){
            compatible.insert(TypeTuile::Eau);
            compatible.insert(TypeTuile::Terre);
            compatible.insert(TypeTuile::Beton);
            compatible.insert(TypeTuile::Arbre);
            //compatible.insert(TypeTuile::Herbe);
        }
        else if(t->obtenirType() == TypeTuile::Beton){
            compatible.insert(TypeTuile::Arbre);
            compatible.insert(TypeTuile::Herbe);
            compatible.insert(TypeTuile::Terre);
        }

        else if(t->obtenirType() == TypeTuile::Terre){
            compatible.insert(TypeTuile::Eau);
            compatible.insert(TypeTuile::Herbe);
            compatible.insert(TypeTuile::Arbre);
        }

        std::pair<int, int > position = p.first;


        int l = position.second, c = position.first;

        Tuile * t_haut_gauche = nullptr, *t_haut = nullptr, *t_haut_droit = nullptr;
        Tuile * t_gauche = nullptr, *t_droit = nullptr;
        Tuile * t_bas_gauche = nullptr, *t_bas = nullptr, *t_bas_droit = nullptr;

        t_haut_gauche = m_position_to_tuile.find(std::make_pair(c-1, l-1)) != m_position_to_tuile.end() ?
                    m_position_to_tuile.find(std::make_pair(c-1, l-1))->second : nullptr;
        t_bas_droit = m_position_to_tuile.find(std::make_pair(c+1, l+1)) != m_position_to_tuile.end() ?
                    m_position_to_tuile.find(std::make_pair(c+1, l+1))->second : nullptr;
        t_haut_droit = m_position_to_tuile.find(std::make_pair(c+1, l-1)) != m_position_to_tuile.end() ?
                    m_position_to_tuile.find(std::make_pair(c+1, l-1))->second : nullptr;
        t_bas_gauche = m_position_to_tuile.find(std::make_pair(c-1, l+1)) != m_position_to_tuile.end() ?
                    m_position_to_tuile.find(std::make_pair(c-1, l+1))->second : nullptr;
        t_haut=  m_position_to_tuile.find(std::make_pair(c, l-1)) != m_position_to_tuile.end() ?
                    m_position_to_tuile.find(std::make_pair(c, l-1))->second : nullptr;
        t_bas =  m_position_to_tuile.find(std::make_pair(c, l+1)) != m_position_to_tuile.end() ?
                    m_position_to_tuile.find(std::make_pair(c, l+1))->second : nullptr;
        t_gauche=  m_position_to_tuile.find(std::make_pair(c-1, l)) != m_position_to_tuile.end() ?
                    m_position_to_tuile.find(std::make_pair(c-1, l))->second : nullptr;
        t_droit =  m_position_to_tuile.find(std::make_pair(c+1, l)) != m_position_to_tuile.end() ?
                    m_position_to_tuile.find(std::make_pair(c+1, l))->second : nullptr;

        TypeTuile voisin = TypeTuile::AucunType;
        TypeJonction jonction = TypeJonction::AucuneJonction;

        // test en bas gauche
        if(t_bas_gauche != nullptr && t_bas_gauche->obtenirType()!=t->obtenirType()){
            // test sortant
            if(t_gauche != nullptr && t_gauche->obtenirType()== t_bas_gauche->obtenirType()){
                if(t_bas != nullptr && t_bas->obtenirType() == t_bas_gauche->obtenirType()){
                    if(compatible.find(t_bas_gauche->obtenirType()) != compatible.end()){
                        voisin = t_bas_gauche->obtenirType();
                        jonction = TypeJonction::BasGaucheSortant;
                    }
                }
            }
            // test entrant
            else if(t_gauche != nullptr && t_gauche->obtenirType()== t->obtenirType())
                if(t_bas != nullptr && t_bas->obtenirType() == t->obtenirType()){
                    if(compatible.find(t_bas_gauche->obtenirType()) != compatible.end()){
                        voisin = t_bas_gauche->obtenirType();
                        jonction = TypeJonction::BasGaucheEntrant;
                    }
                }
        }

        // test en bas droit
        if(t_bas_droit != nullptr && t_bas_droit->obtenirType()!=t->obtenirType()){
            // test sortant
            if(t_droit != nullptr && t_droit->obtenirType()== t_bas_droit->obtenirType()){
                if(t_bas != nullptr && t_bas->obtenirType() == t_bas_droit->obtenirType()){
                    if(compatible.find(t_bas_droit->obtenirType()) != compatible.end()){
                        voisin = t_bas_droit->obtenirType();
                        jonction = TypeJonction::BasDroiteSortant;
                    }
                }
            }
            // test entrant
            else if(t_droit != nullptr && t_droit->obtenirType()== t->obtenirType())
                if(t_bas != nullptr && t_bas->obtenirType() == t->obtenirType()){
                    if(compatible.find(t_bas_droit->obtenirType()) != compatible.end()){
                        voisin = t_bas_droit->obtenirType();
                        jonction = TypeJonction::BasDroiteEntrant;
                    }
                }
        }
        // test haut gauche
        if(t_haut_gauche != nullptr && t_haut_gauche->obtenirType()!=t->obtenirType()){
            // test sortant
            if(t_gauche != nullptr && t_gauche->obtenirType()== t_haut_gauche->obtenirType()){
                if(t_haut != nullptr && t_haut->obtenirType() == t_haut_gauche->obtenirType()){
                    if(compatible.find(t_haut_gauche->obtenirType()) != compatible.end()){
                        voisin = t_haut_gauche->obtenirType();
                        jonction = TypeJonction::HautGaucheSortant;
                    }
                }
            }
            // test entrant
            else if(t_gauche != nullptr && t_gauche->obtenirType()== t->obtenirType())
                if(t_haut != nullptr && t_haut->obtenirType() == t->obtenirType()){
                    if(compatible.find(t_haut_gauche->obtenirType()) != compatible.end()){
                        voisin = t_haut_gauche->obtenirType();
                        jonction = TypeJonction::HautGaucheEntrant;
                    }
                }
        }
        // test haut droit
        if(t_haut_droit != nullptr && t_haut_droit->obtenirType()!=t->obtenirType()){
            // test sortant
            if(t_droit != nullptr && t_droit->obtenirType()== t_haut_droit->obtenirType()){
                if(t_haut != nullptr && t_haut->obtenirType() == t_haut_droit->obtenirType()){
                    if(compatible.find(t_haut_droit->obtenirType()) != compatible.end()){
                        voisin = t_haut_droit->obtenirType();
                        jonction = TypeJonction::HautDroiteSortant;
                    }
                }
            }
            // test entrant
            else if(t_droit != nullptr && t_droit->obtenirType()== t->obtenirType())
                if(t_haut != nullptr && t_haut->obtenirType() == t->obtenirType()){
                    if(compatible.find(t_haut_droit->obtenirType()) != compatible.end()){
                        voisin = t_haut_droit->obtenirType();
                        jonction = TypeJonction::HautDroiteEntrant;
                    }
                }
        }
        // test a gauche
        if(t_gauche != nullptr && t_gauche->obtenirType()!=t->obtenirType()){
            if(t_haut == nullptr || t_haut->obtenirType()!= t_gauche->obtenirType()){
                if(t_bas == nullptr || t_bas->obtenirType()!= t_gauche->obtenirType()){
                    if(compatible.find(t_gauche->obtenirType()) != compatible.end()){
                        voisin = t_gauche->obtenirType();
                        jonction = TypeJonction::Gauche;
                    }
                }
            }
        }
        // test a droite
        if(t_droit != nullptr && t_droit->obtenirType()!=t->obtenirType()){
            if(t_haut == nullptr || t_haut->obtenirType()!= t_droit->obtenirType()){
                if(t_bas == nullptr || t_bas->obtenirType()!= t_droit->obtenirType()){
                    if(compatible.find(t_droit->obtenirType()) != compatible.end()){
                        voisin = t_droit->obtenirType();
                        jonction = TypeJonction::Droite;
                    }
                }
            }
        }
        // test en haut
        if(t_haut != nullptr && t_haut->obtenirType()!=t->obtenirType()){
            if(t_gauche == nullptr || t_gauche->obtenirType()!= t_haut->obtenirType()){
                if(t_droit == nullptr || t_droit->obtenirType()!= t_haut->obtenirType()){
                    if(compatible.find(t_haut->obtenirType()) != compatible.end()){
                        voisin = t_haut->obtenirType();
                        jonction = TypeJonction::Haut;
                    }
                }
            }
        }
        // test en bas
        if(t_bas != nullptr && t_bas->obtenirType()!=t->obtenirType()){
            if(t_gauche == nullptr || t_gauche->obtenirType()!= t_bas->obtenirType()){
                if(t_droit == nullptr || t_droit->obtenirType()!= t_bas->obtenirType()){
                    if(compatible.find(t_bas->obtenirType()) != compatible.end()){
                        voisin = t_bas->obtenirType();
                        jonction = TypeJonction::Bas;
                    }

                }
            }
        }
        t->definirHachageJonction(voisin, jonction);
    }

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
