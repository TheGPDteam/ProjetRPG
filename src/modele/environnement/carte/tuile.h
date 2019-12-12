#ifndef tuile_h
#define tuile_h

#include "direction.h"

enum TypeTuile {
    Sable = 0,
    Herbe,
    Eau,
    Goudron,
    Terre,
    Obstacle,
    SortieDroite,
    SortieGauche,
    SortieHaut,
    SortieBas,
    HerbeDecoration,
    Jointure
};

enum ECategorieTuile {
    NonTerreux = 0,
    Terreux,
    Aqueux,
    EauTerreux,
    ObstacleOrganique,
    ObstacleNonOrganique,
    Sortie
};

class Tuile{
//protected:

private:
    TypeTuile m_type;
    ECategorieTuile m_categorie;
    Direction m_directionChangementZone;
    bool m_marchable;
    int m_numSol;
    int m_numDeco;
public:
    Direction obtenirDirectionChangementZone() const;
    void definirDirectionChangementZone(Direction dir);
    Tuile(int val);
    bool obtenirEstMarchable() const;
    bool obtenirPeutApparaitre() const;
    int obtenirSol() const;
    int obtenirDecoration() const;
    bool estDecoree() const;
    void definirDecoration(int num_decoration);
    void mettreAJourMarcheable(int numero);
};

#endif
