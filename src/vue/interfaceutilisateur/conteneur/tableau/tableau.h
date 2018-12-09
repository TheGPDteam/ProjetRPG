#ifndef TABLEAU_H
#define TABLEAU_H

#include "affichable.h"
#include <vector>
#include "ligne.h"

class Tableau : public Affichable
{
private :
    float m_hauteurLigne;
    int m_nbLignes;
    Ligne * m_enTete;
    std::vector<Ligne*> m_lignes;
    int m_nbLignesMax;
    Controleur *m_controleur;
    void creerLigne(std::vector<std::string> ligne);
    void creerLigne(std::vector<Affichable *> donneesLigne);
    SDL_Rect creerRectLigne();


    void ajouterEnTeteHumain();
    void ajouterEnTeteObjet(TypeObjet typeObjet);
    void ajouterEnTetePartiesBus();

public:
    Tableau(SDL_Rect rect, float hauteurLigne, Controleur *controleur);

    void vider();

    void ajouterLigne(std::vector<Affichable*> affichables);
    void ajouterLigne(Humain* perso);
    void ajouterLigne(Objet* obj);
    void ajouterLigne(Campement *c);

    ZoneTexte *creeZoneTexte(std::string donnee);
    Ligne *ligneSurvole(std::pair<int, int> coord_souris);
    void afficher(SDL_Surface *surface_affichage) override;
    void redimensionner(SDL_Rect nouvelleDimension) override;

    static Tableau * tableauHumain(SDL_Rect rect, float hauteurLigne, Controleur *controleur);
    static Tableau * tableauObjet(SDL_Rect rect, float hauteurLigne, Controleur *controleur, TypeObjet typeObjet=TypeObjet::Objet);
//    static Tableau * tableauCampement(SDL_Rect rect, float hauteurLigne, Controleur *controleur);

};

#endif // TABLEAU_H
