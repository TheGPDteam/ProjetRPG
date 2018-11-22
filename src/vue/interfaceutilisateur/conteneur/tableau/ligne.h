#ifndef LIGNE_H
#define LIGNE_H
#include "affichable.h"
#include "cliquable.h"
#include "case.h"

class Ligne : public Affichable, public Cliquable
{
private:
    std::vector<std::string> m_donnees;
    std::vector<Case*> m_cases;
    SDL_Rect zone() const ;
    void creerCaseString(std::string donnee);
    void creerCaseElement(Affichable* affichable);
    SDL_Rect creerRectCase();
public:
    Ligne() = delete;
    Ligne(std::vector<std::string> donnees, Controleur *controleur, SDL_Rect rectangleParLigne);
    void afficher(SDL_Surface * surface) override;
    void redimensionner(SDL_Rect m_rectangle) override;
    void clique() override;
};

#endif // LIGNE_H
