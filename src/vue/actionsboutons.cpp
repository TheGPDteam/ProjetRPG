#include "actionsboutons.h"


//!
//! \brief Constructeur par défaut
//! \author pgutierrez
//! \date 20/11/16
//! \version 0.1
//!

ActionsBoutons::ActionsBoutons()
{
}


//!
//! \brief Méthode lançant le jeu principale
//! @return TypeEcran retourne le nouveau type de l'écran
//! \author pgutierrez
//! \date 20/11/16
//! \version 1.0
//!
//! Si un bouton "continuer" est cliqué alors on retourne le nouveau type de l'écran
//!

TypeEcran ActionsBoutons::boutonJeuPrincipal() const
{
    return TypeEcran::JeuPrincipal;
}


//!
//! \brief Méthode quittant le jeu
//! @return TypeEcran retourne le nouveau type de l'écran
//! \author pgutierrez
//! \date 20/11/16
//! \version 1.0
//!
//! Si un bouton "quitter" est cliqué alors on quitte le jeu
//!

TypeEcran ActionsBoutons::boutonQuitter() const
{
    return TypeEcran:: Quitter;
}


//!
//! \brief Méthode lançant l'affichage de l'ecran inventaire
//! @return TypeEcran retourne le nouveau type de l'écran
//! \author pgutierrez
//! \date 25/01/17
//! \version 1.0
//!
//! Si un bouton "Inventaire" est cliqué alors on retourne le nouveau type de l'écran
//!

TypeEcran ActionsBoutons::boutonInventaire() const
{
    return TypeEcran::Inventaire;
}


//!
//! \brief Méthode lançant l'affichage de l'ecran equipe
//! @return TypeEcran retourne le nouveau type de l'écran
//! \author pgutierrez
//! \date 25/01/17
//! \version 1.0
//!
//! Si un bouton "Equipe" est cliqué alors on retourne le nouveau type de l'écran
//!

TypeEcran ActionsBoutons::boutonEquipe() const
{
    return TypeEcran::Equipe;
}



//!
//! \brief Méthode lançant l'affichage de l'ecran ChoixPersonnage
//! @return TypeEcran retourne le nouveau type de l'écran
//! \author pgutierrez
//! \date 18/10/17
//! \version 1.0
//!
//! Si un bouton "ChoixPersonnage" est cliqué alors on retourne le nouveau type de l'écran
//!
TypeEcran ActionsBoutons::boutonChoixPersonnage() const
{
    return TypeEcran::ChoixPersonnage;
}
TypeEcran ActionsBoutons::boutonQuete() const
{
    return TypeEcran::ChoixQuete;
}
TypeEcran ActionsBoutons::boutonChoixJoueur() const
{
    return TypeEcran::PopUpJoueur;
}
TypeEcran ActionsBoutons::boutonChasseJoueur() const
{
    return TypeEcran::ChasseJoueur;
}
TypeEcran ActionsBoutons::boutonRecolteJoueur() const
{
    return TypeEcran::RecolteJoueur;
}

//!
//! \brief Méthode lançant l'affichage de l'écran de l'histoire
//! @return TypeEcran retourne le nouveau type de l'écran
//! \author pgutierrez
//! \date 20/11/17
//! \version 1.0
//!
//! Si un bouton "NouvellePartie" est cliqué alors on retourne le nouveau type de l'écran
//!
TypeEcran ActionsBoutons::boutonNouvellePartie() const
{
    return TypeEcran::PremiereJournee;
}
TypeEcran ActionsBoutons::boutonChoixNom() const
{
    return TypeEcran::choixNom;
}
