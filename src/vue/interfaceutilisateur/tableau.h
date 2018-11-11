#ifndef TABLEAU_H
#define TABLEAU_H

#include "../affichable.h"
#include <vector>
#include "ligne.h"

class Tableau : public Affichable
{
private :
    float m_hauteurLigne;
    float m_hauteur;
    float m_largeur;
    Ligne * m_enTete;
    std::vector<Ligne*> m_lignes;
    int m_nbLignesMax;
public:
    Tableau(SDL_Rect rect, float hauteur, float largeur, float hauteurLigne, Ligne* enTete);
    void ajouterElement(std::vector<Affichable*> affichables);
    void afficher(SDL_Surface *surface_affichage) override;
    void redimensionner(SDL_Rect nouvelleDimension) override;

};

#endif // TABLEAU_H
