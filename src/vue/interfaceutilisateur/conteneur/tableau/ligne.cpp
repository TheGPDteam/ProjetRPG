#include "ligne.h"

Ligne::Ligne(std::vector<std::string> donnees, float hauteurLigne, Controleur * controleur, SDL_Rect rectangleParLigne)
    : Affichable(rectangleParLigne), Cliquable(controleur, /*action,*/ true), m_donnees(donnees)
{

}

void Ligne::afficher(SDL_Surface *surface)
{
//    for (Case * c : m_cases)
//    {
//        //TODO SOMETHING
//        c->afficher(surface);
//    }
}

void Ligne::redimensionner(SDL_Rect m_rectangle)
{
    //TODO
}

bool Ligne::contient(std::pair<int, int> coord_souris) const
{
    //Si souris est dans le rectangle d'affichage
//    for (Case * c : m_cases)
//    {
//        c->contient(coord_souris);
//    }
}

void Ligne::clique() {

}

SDL_Rect Ligne::zone() const{
    return SDL_Rect();
}
