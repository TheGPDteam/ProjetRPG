#ifndef TABLEAU_H
#define TABLEAU_H

#include "affichable.h"
#include <vector>
#include "zonedefilable.h"
#include "ligne.h"

class Tableau : public Affichable
{
private :
    float m_hauteurLigne;
    bool m_avecImage;
    std::vector<Ligne*> m_lignes;
    Controleur *m_controleur;
    Ligne * m_lignePrecedemmentSurvoler = nullptr;
    void creerLigne(std::vector<std::string> ligne);
    void creerLigne(std::vector<Affichable *> donneesLigne);
    SDL_Rect creerRectLigne();
    SDL_Rect creerRectLigne(int numLigne);

    void ajouterEnTeteHumain();
    void ajouterEnTeteObjet(TypeObjet typeObjet);
    void ajouterEnTetePartiesBus();
    int positionLigne(Ligne * ligRecherchee);

public:
    Tableau(SDL_Rect rect, Controleur *controleur,bool avecImage, float hauteurLigne);
    void vider();
    void ajouterLigne(std::vector<Affichable*> affichables);
    void ajouterLigne(std::vector<std::string> strings);
    void ajouterLigne(Humain* perso);
    void ajouterLigne(Objet* obj);
    void ajouterLigne(Campement *c);
    bool trie(Case * c);
    int obtenirNbLignes();
    Ligne * obtenirLigne(int numLigne);
    bool testAffichageLigneSurvole(std::pair<int, int> coord_souris);
    ZoneTexte *creeZoneTexte(std::string donnee, COMPORTEMENT_TEXTE comportement = COMPORTEMENT_TEXTE::REDIMENTIONNE, ALIGNEMENT_TEXTE alignement = ALIGNEMENT_TEXTE::CENTRE);
    Ligne *ligneSurvole(std::pair<int, int> coord_souris);
    ZoneDefilable * obtenirZoneDefilableTableau(SDL_Rect rectAffichable);
    void afficher(SDL_Surface *surface_affichage) override;
    void redimensionner(SDL_Rect nouvelleDimension) override;



//    static Tableau * tableauCampement(SDL_Rect rect, float hauteurLigne, Controleur *controleur);

};

#endif // TABLEAU_H
