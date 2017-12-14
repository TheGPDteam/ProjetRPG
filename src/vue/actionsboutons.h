#ifndef ACTIONSBOUTONS_H
#define ACTIONSBOUTONS_H

#include "typeecran.h"

class ActionsBoutons
{
public:
    ActionsBoutons();

    TypeEcran boutonJeuPrincipal() const;

    TypeEcran boutonQuete() const;

    TypeEcran boutonQuitter() const;

    TypeEcran boutonChoixPersonnage() const;

    TypeEcran boutonEquipe() const;

    TypeEcran boutonInventaire() const;

    TypeEcran boutonChoixJoueur() const;

    TypeEcran boutonRecolteJoueur() const;

    TypeEcran boutonChasseJoueur() const;

    TypeEcran boutonChoixNom() const;

};

#endif // ACTIONSBOUTONS_H
