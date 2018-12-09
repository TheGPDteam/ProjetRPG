#ifndef CASE_H
#define CASE_H

#include "affichable.h"
#include <iostream>
#include "zonetexte.h"
#include "policetexte.h"


class Case : public Affichable
{
private :
    Affichable* m_donnee;

public :
    Case(SDL_Rect rect, Affichable* donnee);
    Case() = delete;
    ~Case();

    void afficher(SDL_Surface *surface) override;
    void redimensionner(SDL_Rect m_rectangle) override;

    void definirDonnee(Affichable* donnee);
    Affichable* obtenirDonnee() const;
};

#endif // CASE_H
