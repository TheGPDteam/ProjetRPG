#include "actionsboutons.h"


//!
//! \brief Constructeur par défaut
//! \author pgutierrez
//! \date 20/11/16
//! \version 0.1
//!

ActionsBoutons::ActionsBoutons(Controleur * controleur)
    :m_controleur{controleur}
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

TypeEcran ActionsBoutons::boutonQuete() const {
    return TypeEcran::ChoixQuete;
}

TypeEcran ActionsBoutons::boutonQueteAcceptation()
{
    m_controleur->choixNouvelArrivant(true);
    m_controleur->obtenirModele()->obtenirJoueur()->obtenirQuete()->definirValeurObjectif(m_controleur->obtenirModele()->obtenirCampement()->obtenirConsommation());
    return TypeEcran::ChoixQuete;
}

TypeEcran ActionsBoutons::boutonQueteRefus()
{
    m_controleur->choixNouvelArrivant(false);
    return TypeEcran::ChoixQuete;
}

TypeEcran ActionsBoutons::boutonChoixJoueur() const
{
    return TypeEcran::PopUpJoueur;
}
TypeEcran ActionsBoutons::boutonChasseJoueur() const
{
    m_controleur->obtenirModele()->reinitialiserTemps();
    m_controleur->obtenirModele()->obtenirJoueur()->definirEquipe(m_controleur->obtenirModele()->obtenirCampement()->obtenirChasse());
    return TypeEcran::ChasseJoueur;
}
TypeEcran ActionsBoutons::boutonRecolteJoueur() const
{
    m_controleur->obtenirModele()->reinitialiserTemps();
    m_controleur->obtenirModele()->obtenirJoueur()->definirEquipe(m_controleur->obtenirModele()->obtenirCampement()->obtenirRecolte());
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

TypeEcran ActionsBoutons::boutonViderInventaire() {
    if(m_controleur->obtenirModele()->obtenirJoueur()->obtenirInventaireJoueur()->obtenirNombreObjet()!=0) {
        std::vector<Objet*> objets = m_controleur->obtenirModele()->obtenirJoueur()->obtenirInventaireJoueur()->obtenirObjets();
        for (Objet* obj : objets) {
            m_controleur->obtenirModele()->obtenirCampement()->ajouterObjet(obj);
            m_controleur->obtenirModele()->obtenirJoueur()->obtenirInventaireJoueur()->supprimerObjet(obj);
        }
        m_controleur->obtenirModele()->obtenirJoueur()->mettreAChange();
        m_controleur->obtenirModele()->obtenirJoueur()->notifierTous();
    }
    return TypeEcran::Inventaire;
}

TypeEcran ActionsBoutons::boutonFinirQuete() {
    m_controleur->finJournee();
    return TypeEcran::RecapitulatifNuit;
}

TypeEcran ActionsBoutons::boutonChoixPersonnageCycle() {
    m_controleur->journeeSuivante();
    return TypeEcran::ChoixPersonnage;
}


TypeEcran ActionsBoutons::boutonChargement() {
    m_controleur->chargerSauvegarde();
    return TypeEcran::ChoixQuete;
}

TypeEcran ActionsBoutons::boutonRetourMenuPrincipal() {
    return TypeEcran::MenuPrincipal;
}

TypeEcran ActionsBoutons::boutonCampement() {
    return TypeEcran::AccueilCampement;
}
