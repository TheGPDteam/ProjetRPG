#ifndef LIGNE_H
#define LIGNE_H
#include <vector>
#include "affichable.h"
#include "cliquable.h"
#include "case.h"

class Ligne : public Affichable, public Cliquable
{
private:
    std::vector<Affichable *> m_donnees;
    std::vector<Case*> m_cases;
    bool m_possedeImage;
    const int TAILLE_IMAGE = 64;
    int m_numCouleur;
    void creerCaseString(std::string donnee);
    void creerCaseElement(Affichable* affichable, bool premiereColonne);
    SDL_Rect creerRectCase();
    SDL_Rect creerRectImage();
    Affichable *m_affichable;
    int numCaseSelTri=0;

public:
    const int m_idLigne;
    Ligne() = delete;
    Ligne(std::vector<Affichable *> donnees, Controleur * controleur, SDL_Rect rectangleLigne, int sombre, int idLigne, bool avecImage);
    Case * caseClique(std::pair<int, int> coord_souris);
    void afficher(SDL_Surface * surface) override;
    void redimensionner(SDL_Rect m_rectangle) override;
    void clique() override;
    SDL_Rect zone() const override;
    Case * obtenirCase(int numCase) const;
    void definirNumCaseSelectionnerTri(int numCase);
    void definirNumCouleur(int sombre);
    int obtenirNumCaseSelectionnerTri();
    bool operator< (const Ligne &otherLig) const;

};

#endif // LIGNE_H
