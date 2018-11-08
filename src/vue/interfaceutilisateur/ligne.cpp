#include "ligne.h"

Ligne::Ligne(std::vector<Case *> cases, SDL_Rect affichable, Controleur * controleur, void* action, bool actif )
    : Affichable(affichable), Cliquable(controleur, action, actif), m_cases{cases}
{

}

void Ligne::afficher(SDL_Surface *surface)
{
    for (Case * c : m_cases)
    {
        //TODO SOMETHING
        c->afficher(surface);
    }
}

void Ligne::redimensionner(SDL_Rect m_rectangle)
{
    //TODO
}

bool Ligne::contient(std::pair<int, int> &coord_souris)
{
    //Si souris est dans le rectangle d'affichage
//    for (Case * c : m_cases)
//    {
//        c->contient(coord_souris);
//    }
}
