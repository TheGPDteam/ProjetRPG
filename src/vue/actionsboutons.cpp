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
    return JeuPrincipal;
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
    return Quitter;
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
    return Inventaire;
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
    return Equipe;
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
    return ChoixPersonnage;
}
TypeEcran ActionsBoutons::boutonQuete() const
{
    return ChoixQuete;
}
TypeEcran ActionsBoutons::boutonChoixJoueur() const
{
    return PopUpJoueur;
}
TypeEcran ActionsBoutons::boutonChasseJoueur() const
{
    return ChasseJoueur;
}
TypeEcran ActionsBoutons::boutonRecolteJoueur() const
{
    return RecolteJoueur;
}
