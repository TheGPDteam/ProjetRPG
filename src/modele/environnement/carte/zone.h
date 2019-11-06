#ifndef zone_h
#define zone_h

#include <vector>
#include <map>
#include <utility>
#include <string>
#include "../../objets/objet.h"
#include "../../survie/vivre.h"
#include "partiebus.h"
#include "arme.h"
#include "tuile.h"
#include "observable.h"

const int DECALAGE_TUILE = 6;
const int MAX_TUILES_EAU_PER_ZONE = 50;
const int MAX_TUILES_TERRE_PER_ZONE = 100;
const int MAX_TUILES_SABLE_PER_ZONE = 100;
const int MAX_TUILES_ARBRE_PER_ZONE = 50;


const int MAX_GROUPES_TUILES_EAU = 10;
const int MAX_GROUPES_TUILES_TERRE = 15;
const int MAX_GROUPES_TUILES_SABLE = 15;
const int MAX_GROUPES_TUILES_ARBRE = 10;

const int TAILLE_ZONE = 76;
class Zone : public Observable{
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
    void initialiserSousTypeTuile();
    std::string valeurDe(std::ifstream fichier, std::string valeur);
public:
    Zone(int longueur, int largeur);
    Zone(std::ifstream fichier);
    ~Zone();
    void init(std::ifstream fichier);
    void init(int largeur, int hauteur);

    Tuile* obtenirTuile(int valeurX, int valeurY) const;
    Tuile* obtenirTuile(std::pair <int,int> position) const;
    Objet* obtenirObjet(std::pair <int,int> position) const;
    bool objetPresent(std::pair<int,int> position) const;
    void supprimerObjet(Objet* obj);
    std::map<Objet*, std::pair<int, int> > obtenirObjets() const;
	std::string obtenirNom();
    void definirNom(std::string nom);
    std::map <Tuile*, std::pair<int,int>> obtenirTuiles() const;
    int obtenirTaille() const;
    void recharger();
};

#endif
