#ifndef LIGNE_H
#define LIGNE_H
#include "../affichable.h"
#include "cliquable.h"
#include "conteneur/tableau/case.h"

class Ligne : public Affichable, public Cliquable
{
private:
    std::vector<std::string> m_donnees;
public:
    Ligne() = delete;
    Ligne(std::vector<std::string> donnees, float hauteurLigne, Controleur controleur, SDL_Rect rectangleParLigne);
    void afficher(SDL_Surface * surface) override;
    void redimensionner(SDL_Rect m_rectangle) override;
    virtual bool contient(std::pair<int, int> coord_souris) const override;
};

#endif // LIGNE_H
