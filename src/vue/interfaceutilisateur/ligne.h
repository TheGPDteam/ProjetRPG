#ifndef LIGNE_H
#define LIGNE_H
#include "../affichable.h"
#include "cliquable.h"

class Ligne : public Affichable, public Cliquable
{
private:
    std::vector<Case *> m_cases;
public:
    Ligne() = delete;
    Ligne(std::vector<Case *> cases, SDL_Rect affichable, Controleur * controleur, void* action, bool actif );
    void afficher(SDL_Surface * surface) override;
    void redimensionner(SDL_Rect m_rectangle) override;
    bool contient(std::pair<int, int> &coord_souris) const override;
    void clique() override;
};

#endif // LIGNE_H
