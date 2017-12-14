#include "zone.h"
#include <utility>
#include <set>
#include <iostream>

//! \file fichier zone
//! \date 17/11/16
//! \version 1.0

Zone::Zone(int longueur, int largeur)
    : m_largeur{largeur},
      m_hauteur{longueur}
{
    initZone();
}

void ligne2Tuile(std::vector<std::string> fichier, std::vector<int> &tuiles, int i)
{

    for (int j=0;j<129; ++j)
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

Zone::Zone(int longueur, int largeur, std::vector<std::string> fichier)
    : m_largeur{largeur},
      m_hauteur{longueur}
{
    for (unsigned int i=0; i<fichier.size();++i)
    {
        std::vector<int> valeursTuiles;
        ligne2Tuile(fichier,valeursTuiles,i);
        for (unsigned int j=0; j<valeursTuiles.size();++j)
        {
            if ((valeursTuiles[j]/6) == 0)
            {
                Tuile * t = new Tuile((TypeTuile)valeursTuiles[j]);
                m_tuiles.insert(std::make_pair(t,std::make_pair(j,i)));
                m_position_to_tuile[std::make_pair(j,i)] = t;
            }
            else if ((valeursTuiles[j]/6) == 1)
            {
                std::cout << "J'ai une tuile extreme de niveau " << valeursTuiles[j] % 6 << std::endl;
                Tuile * t = new Tuile((TypeTuile)valeursTuiles[j] % 6);
                t->definirExtremiteCarte(true);
                m_tuiles.insert(std::make_pair(t,std::make_pair(j,i)));
                m_position_to_tuile[std::make_pair(j,i)] = t;
            }
            else
            {
                Tuile * t = new Tuile((TypeTuile)2);
                m_tuiles.insert(std::make_pair(t,std::make_pair(j,i)));
                m_position_to_tuile[std::make_pair(j,i)] = t;
            }
        }
    }
    ajouterObjets(20);
}

Zone::~Zone()
{
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

Tuile* Zone::obtenirTuile(int valeurX, int valeurY) const
{
    std::pair<int,int> position;
    position.first=valeurX;
    position.second=valeurY;
    for (auto it = m_tuiles.begin(); it != m_tuiles.end(); ++it )
        if (it->second == position)
            return it->first;
}

Tuile* Zone::obtenirTuile(std::pair <int,int> position) const
{
    for (auto it = m_tuiles.begin(); it != m_tuiles.end(); ++it )
        if (it->second == position)
            return it->first;
}

Objet* Zone::obtenirObjet(std::pair <int,int> position) const
{
    for (auto it = m_objets.begin(); it != m_objets.end(); ++it )
        if (it->second == position)
            return it->first;
    return NULL;
}

bool Zone::objetPresent(std::pair<int, int> position) const
{
    for (auto it = m_objets.begin(); it != m_objets.end(); ++it )
    {
        if (it->second == position)
        {
            return true;
        }
    }
    return false;
}

void Zone::supprimerObjet(Objet* obj)
{
    m_objets.erase(m_objets.find(obj));
}

std::map <Objet*,std::pair <int,int>> Zone::obtenirObjets() const
{
    return m_objets;
}

std::string Zone::obtenirNom()
{
    return m_nom;
}

std::map<Tuile *, std::pair<int, int> > Zone::obtenirTuiles() const
{
    return m_tuiles;
}

int Zone::obtenirTaille() const {
    return m_largeur;
}

void Zone::initZone()
{
    for(int i=0;i<m_hauteur;i++)
    {
        for(int j=0;j<m_largeur;j++)
        {
            Tuile * t = new Tuile((TypeTuile)2);
            m_tuiles.insert(std::make_pair(t,std::make_pair(i,j)));
            m_position_to_tuile[std::make_pair(i,j)] = t;
        }
    }

    m_objets.insert(std::make_pair(new Objet{"Oreille de zombie", "Ouloulou, probablement tombée par hasard d'un zombie, vous devriez courir."}, std::make_pair(42,42)));


    ajouterSols(Eau, MAX_TUILES_EAU_PER_ZONE, MAX_GROUPES_TUILES_EAU);
    ajouterSols(Sable, MAX_TUILES_SABLE_PER_ZONE, MAX_GROUPES_TUILES_SABLE);
    ajouterSols(Terre, MAX_TUILES_TERRE_PER_ZONE, MAX_GROUPES_TUILES_TERRE);

    ajouterObjets(20);

}

void Zone::ajouterSols(int typeSol, int maxTypeSol, int maxGroupe)
{

    int nbGroupeTuileEau = rand() % maxGroupe;
    for(int j = 0 ; j < nbGroupeTuileEau; ++j){
        int posX = rand() % m_largeur;
        int posY = rand() % m_hauteur;

        int nbTuiles = rand() % maxTypeSol ;

        Tuile * t = m_position_to_tuile.at(std::make_pair(posX, posY));
        m_tuiles.erase(t);
        delete t;
        t = new Tuile((TypeTuile)typeSol);
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

            t = new Tuile(((TypeTuile)typeSol));
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

void Zone::ajouterObjets(int nbObjets)
{
    for (int i=0;i<nbObjets;++i)
    {
        int posX = rand() % m_largeur;
        int posY = rand() % m_hauteur;

        Tuile * t  = m_position_to_tuile.at(std::make_pair(posX,posY));

        // Permet de verifier que la tuile puisse contenir des objets & qu'il n'y a pas d'objet deja present
        while (!t->obtenirPeutApparaitre() && !objetPresent(std::make_pair(posX,posY)))
        {
            posX = rand() % m_largeur;
            posY = rand() % m_hauteur;
            t = m_position_to_tuile.at(std::make_pair(posX,posY));
        }

        //Ajouter l'objet sur la tuile /*A revoir pour un objet aléatoire*/
        int typeObj = rand()%3;
        switch (typeObj) {
        case 0:
            m_objets.insert(std::make_pair(new Vivre(),std::make_pair(posX,posY)));
            break;
        case 1:
            m_objets.insert(std::make_pair(new Arme() ,std::make_pair(posX,posY)));
            break;
        case 2:
            m_objets.insert(std::make_pair(new Objet("Montre du temps","Permet de garder un oeil sur le temps"),std::make_pair(posX,posY)));
            break;
        default:
            break;
        }
    }
}
