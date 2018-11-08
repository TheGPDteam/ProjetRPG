#ifndef TABLEAU_H
#define TABLEAU_H

#include "../affichable.h"
#include <vector>

class Tableau : public Affichable
{
private :
    const float hauteurLigne;
    const float hauteur, largeur;
    Ligne *enTete;
    std::vector<Ligne*> lignes;
    int nbLignesMax, nbColonnesMax;
public:
    Tableau(const float hauteur,const float largeur, const float hauteurLigne);
    void ajouterElement(std::vector<Affichable*> affichables);
    void afficher(SDL_Surface *surface_affichage) override;
    void redimensionner(SDL_Rect nouvelleDimension) override;

};

#endif // TABLEAU_H
