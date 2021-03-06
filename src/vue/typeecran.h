#ifndef TYPEECRAN_H
#define TYPEECRAN_H

const int WIDTH_FENETRE_PRINCIPALE = 1024;
const int HEIGHT_FENETRE_PRINCIPALE = 668;
const int BPP = 12;

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
