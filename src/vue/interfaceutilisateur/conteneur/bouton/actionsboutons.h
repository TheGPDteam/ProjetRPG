#ifndef ACTIONSBOUTONS_H
#define ACTIONSBOUTONS_H

#include "../../../ecran/typeecran.h"
#include "controleur/controleur.h"

class ActionsBoutons
{
private:
    Controleur * m_controleur;
public:
    ActionsBoutons(Controleur * controleur);

    TypeEcran boutonJeuPrincipal() const;

    TypeEcran boutonQuete() const;
    TypeEcran boutonQueteAcceptation();
    TypeEcran boutonQueteRefus();

    TypeEcran boutonQuitter() const;

    TypeEcran boutonChoixPersonnage() const;

    TypeEcran boutonEquipe() const;

    TypeEcran boutonInventaire() const;

    TypeEcran boutonChoixJoueur() const;

    TypeEcran boutonRecolteJoueur() const;

    TypeEcran boutonChasseJoueur() const;

    TypeEcran boutonChoixNom() const;

    TypeEcran boutonNouvellePartie() const;
    TypeEcran boutonViderInventaire();

    TypeEcran boutonFinirQuete();

    TypeEcran boutonChargement();

    TypeEcran boutonChoixPersonnageCycle();

    TypeEcran boutonRetourMenuPrincipal();

    TypeEcran boutonCampement();

    TypeEcran boutonViderInventaireCampement();

    TypeEcran boutonListeObjet();

    TypeEcran boutonJeuPrincipalCampement();
};

#endif // ACTIONSBOUTONS_H
