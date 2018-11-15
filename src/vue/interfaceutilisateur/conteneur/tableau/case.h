#ifndef CASE_H
#define CASE_H

#include "../../../affichable.h"
#include <iostream>
#include "../../zonetexte.h"
#include "../../ressources/policetexte.h"


class Case : public Affichable
{
private :
    Affichable* m_donnee;

public :
    Case(SDL_Rect rect, Affichable* donnee);
    Case(SDL_Rect rect, std::string donnee);
    Case() = delete;
    ~Case();

    void afficher(SDL_Surface *surface);
    void redimensionner(SDL_Rect m_rectangle);

    void definirDonnee(Affichable* donnee);
    Affichable* obtenirDonnee() const;
};

#endif // CASE_H
