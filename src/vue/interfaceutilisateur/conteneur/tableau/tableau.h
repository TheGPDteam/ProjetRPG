#ifndef TABLEAU_H
#define TABLEAU_H

#include "affichable.h"
#include <vector>
#include "ligne.h"

class Tableau : public Affichable
{
private :
    float m_hauteur;
    float m_largeur;
    float m_hauteurLigne;
    Ligne * m_enTete;
    std::vector<Ligne*> m_lignes;
    int m_nbLignesMax;
    Controleur *m_controleur;

    void creeLigne(std::vector<std::string> ligne);

public:
    Tableau(SDL_Rect rect, float hauteur, float largeur, float hauteurLigne, Ligne* enTete, Controleur *controleur);
    void ajouterElement(std::vector<Affichable*> affichables);
    void ajouterHumain(Humain* perso);
    void ajouterObjet(Objet* obj);

    void afficher(SDL_Surface *surface_affichage) override;
    void redimensionner(SDL_Rect nouvelleDimension) override;

};

#endif // TABLEAU_H