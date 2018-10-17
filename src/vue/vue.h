#ifndef vue_h
#define vue_h

#include "controleur/controleur.h"
#include "./ecran/menu/ecranmenuprincipal.h"
#include "./ecran/jeu/ecranjeuprincipal.h"
#include "./ecran/jeu/ecranequipe.h"
#include "./ecran/jeu/ecranchoixpersonnage.h"
#include "./ecran/menu/ecranquete.h"
#include "./ecran/jeu/ecraninventaire.h"
#include "./ecran/menu/ecranquetejoueur.h"
#include "./ecran/menu/ecrannom.h"
#include "./ecran/menu/ecranrecapitulatifnuit.h"
#include "./ecran/menu/ecranpremierejournee.h"
#include "./ecran/menu/ecranaccueilcampement.h"
#include "./ecran/jeu/ecranlisteobjets.h"

#include <iostream>

class Vue
{
private:
    SDL_Surface* m_fenetrePrincipale;

    TypeEcran m_typeEcran;

    EcranMenuPrincipal* m_menuPrincipal;
    EcranJeuPrincipal* m_jeuPrincipal;
    EcranEquipe* m_ecranEquipe;
    EcranInventaire* m_ecranInventaire;
    EcranChoixPersonnage* m_ecranChoixPersonnage;
    EcranQuete* m_ecranChoixQuete;
    EcranQueteJoueur* m_ecranQueteJoueur;
    EcranNom* m_ecranNom;
    EcranPremiereJournee* m_ecranPremiereJournee;
    EcranRecapitulatifNuit* m_ecranRecapitulatifNuit;
    EcranAccueilCampement* m_ecranAccueilCampement;
    EcranListeObjet* m_ecranListeObjet;

    Controleur* m_controleur;

    bool m_cliqueSouris;
    std::pair<int, int> m_coordSouris;
    bool m_quitterJeu;

    const int DELAI = 36;

    void afficherEcran(EcranGeneral* ecran_courant);

public:
    Vue();
    void definirControleur(Controleur * controleur);
    void affichageVue();
    void gestionEvenementJoueur();

    SDL_Surface* obtenirFenetrePrincipale();

    void changerEcran(TypeEcran nouvelEcran);

    bool getFermerJeu();

    ~Vue();
};

#endif
