#ifndef TYPEECRAN_H
#define TYPEECRAN_H

const int WIDTH_FENETRE_PRINCIPALE = 1024;
const int HEIGHT_FENETRE_PRINCIPALE = 668;
const int BPP = 32;

//!
//! Représente tout les type d'écran possible
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
//!

enum TypeEcran
{
    MenuPrincipal, JeuPrincipal, Quitter, Inventaire, Equipe, ChoixQuete
};

#endif // TYPEECRAN_H
