#ifndef TYPEECRAN_H
#define TYPEECRAN_H

#define WIDTH_FENETRE_PRINCIPALE 1216
#define HEIGHT_FENETRE_PRINCIPALE 704
#define BPP 12

//!
//! Représente tout les types d'écran possibles
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
//!

enum class TypeEcran
{
    MenuPrincipal, JeuPrincipal, Quitter, Inventaire, Equipe, ChoixPersonnage, ChoixQuete, PopUpJoueur,RecolteJoueur, ChasseJoueur, RecapitulatifNuit, PremiereJournee, choixNom, AccueilCampement, ListeObjet, QueteCampement
};
#endif // TYPEECRAN_H
