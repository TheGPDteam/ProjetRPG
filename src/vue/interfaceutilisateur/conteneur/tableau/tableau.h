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
    int m_nbLignes;
    bool m_avecImage;
    Ligne * m_titre;
    Ligne * m_enTete;
    std::vector<Ligne*> m_lignes;
    int m_nbLignesMax;
    Controleur *m_controleur;
    Ligne * m_lignePrecedemmentSurvoler = nullptr;
    void creerLigne(std::vector<std::string> ligne);
    void creerLigne(std::vector<Affichable *> donneesLigne);
    SDL_Rect creerRectLigne();
    SDL_Rect creerRectLigne(int numLigne);
    void trie(Case * c);

    void ajouterEnTeteHumain();
    void ajouterEnTeteObjet(TypeObjet typeObjet);
    void ajouterEnTetePartiesBus();
    int positionLigne(Ligne * ligRecherchee);

public:
    Tableau(SDL_Rect rect, float hauteurLigne, Controleur *controleur, std::string nom, bool avecImage);
    void vider();
    void ajouterLigne(std::vector<Affichable*> affichables);
    void ajouterLigne(Humain* perso);
    void ajouterLigne(Objet* obj);
    void ajouterLigne(Campement *c);
    bool testTri(Ligne * l, std::pair<int, int> coord_souris);
    void trieDefault();
    void testAffichageLigneSurvole(std::pair<int, int> coord_souris);
    ZoneTexte *creeZoneTexte(std::string donnee);
    Ligne *ligneSurvole(std::pair<int, int> coord_souris);
    ZoneDefilable * zoneDefilableTableau(SDL_Rect rectAffichable);
    void afficher(SDL_Surface *surface_affichage) override;
    void redimensionner(SDL_Rect nouvelleDimension) override;

    static Tableau * tableauHumain(SDL_Rect rect, float hauteurLigne, Controleur *controleur, const std::string titre, bool aUneImage);
    static Tableau * tableauObjet(SDL_Rect rect, float hauteurLigne, Controleur *controleur, const std::string titre, bool aUneImage, TypeObjet typeObjet=TypeObjet::Objet);


//    static Tableau * tableauCampement(SDL_Rect rect, float hauteurLigne, Controleur *controleur);

};

#endif // TABLEAU_H
