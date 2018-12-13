#ifndef LIGNE_H
#define LIGNE_H
#include "affichable.h"
#include "cliquable.h"
#include "case.h"

class Ligne : public Affichable, public Cliquable
{
private:
    std::vector<Affichable *> m_donnees;
    std::vector<Case*> m_cases;
    int m_sombre;
    void creerCaseString(std::string donnee);
    void creerCaseElement(Affichable* affichable);
    SDL_Rect creerRectCase();
    Affichable *m_affichable;
public:
    const int m_idLigne;
    Ligne() = delete;
    Ligne(std::vector<Affichable *> donnees, Controleur * controleur, SDL_Rect rectangleLigne, int sombre, int idLigne);
    Case * caseClique(std::pair<int, int> coord_souris);
    void afficher(SDL_Surface * surface) override;
    void redimensionner(SDL_Rect m_rectangle) override;
    void clique() override;
    SDL_Rect zone() const ;
};

#endif // LIGNE_H
