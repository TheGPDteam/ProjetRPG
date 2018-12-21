#ifndef CASE_H
#define CASE_H

#include "affichable.h"
#include <iostream>
#include "zonetexte.h"
#include "policetexte.h"
#include "cliquable.h"


class Case : public Affichable, public Cliquable
{
private :
    Affichable* m_donnee;
    int m_id;

public :
    Case(SDL_Rect rect, Affichable * donnee, Controleur * controleur, int idCase);
    Case() = delete;
    ~Case();
    int obtenirIdCase() const;
    void afficher(SDL_Surface *surface) override;
    void redimensionner(SDL_Rect rectangle) override;
    void clique() override;

    void definirDonnee(Affichable* donnee);
    Affichable* obtenirDonnee() const;
    SDL_Rect zone() const;
};

#endif // CASE_H
