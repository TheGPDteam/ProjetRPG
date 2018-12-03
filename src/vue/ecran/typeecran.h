#ifndef TYPEECRAN_H
#define TYPEECRAN_H

#define WIDTH_FENETRE_PRINCIPALE 1024
#define HEIGHT_FENETRE_PRINCIPALE 668
#define BPP 12

//!
//! Représente tout les types d'écran possibles
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
//!

enum class TypeEcran
{
    MenuPrincipal, JeuPrincipal, Quitter, Inventaire, Equipe, ChoixPersonnage, ChoixQuete, PopUpJoueur,RecolteJoueur, ChasseJoueur, RecapitulatifNuit, PremiereJournee, choixNom, AccueilCampement, ListeObjet
};
#endif // TYPEECRAN_H
