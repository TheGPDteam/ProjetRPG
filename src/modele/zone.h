#ifndef zone_h
#define zone_h

#include <vector>
#include <map>
#include <utility>
#include <string>
#include "objet.h"
#include "tuile.h"
#include "observable.h"

const int MAX_TUILES_EAU_PER_ZONE = 50;
const int MAX_TUILES_TERRE_PER_ZONE = 100;
const int MAX_TUILES_SABLE_PER_ZONE = 100;
const int MAX_TUILES_ARBRE_PER_ZONE = 50;


const int MAX_GROUPES_TUILES_EAU = 10;
const int MAX_GROUPES_TUILES_TERRE = 15;
const int MAX_GROUPES_TUILES_SABLE = 15;
const int MAX_GROUPES_TUILES_ARBRE = 10;

class Zone
{
private:
    std::map<Objet*,std::pair<int,int>> m_objets;
	int m_largeur;
    int m_hauteur;
	std::string m_nom;
	std::vector <std::pair<std::string,std::pair<int,int>>> m_zonesVoisines;
    std::map <Tuile*, std::pair<int,int>> m_tuiles;
    std::map <std::pair<int,int>, Tuile*> m_position_to_tuile;

    void initZone();
    void ajouterSols(int typeSol, int maxTypeSol, int maxGroupe);
    void ajouterObjets(int nbObjets);

public:

    Zone()=default;
    Zone(int longueur, int largeur);
    Zone(int longueur, int largeur, std::vector<std::string> fichier);
    ~Zone();

    Tuile* obtenirTuile(int valeurX, int valeurY) const;
    Tuile* obtenirTuile(std::pair <int,int> position) const;
    Objet* obtenirObjet(std::pair <int,int> position) const;
    bool objetPresent(std::pair<int,int> position) const;
    void supprimerObjet(Objet* obj);
    std::map<Objet*, std::pair<int, int> > obtenirObjets() const;
	std::string obtenirNom();
    std::map <Tuile*, std::pair<int,int>> obtenirTuiles() const;
    int obtenirTaille() const;

};

#endif
