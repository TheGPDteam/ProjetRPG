#ifndef ACTIONSBOUTONS_H
#define ACTIONSBOUTONS_H

#include "typeecran.h"

class ActionsBoutons
{
public:
    ActionsBoutons();

    TypeEcran boutonJeuPrincipal() const;

    TypeEcran boutonQuitter() const;

    TypeEcran boutonEquipe() const;

    TypeEcran boutonInventaire() const;

};

#endif // ACTIONSBOUTONS_H
