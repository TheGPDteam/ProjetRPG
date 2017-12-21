#ifndef vue_h
#define vue_h

#include "controleur/controleur.h"
#include "ecranmenuprincipal.h"
#include "ecranjeuprincipal.h"
#include "ecranequipe.h"
#include "ecranchoixpersonnage.h"
#include "ecranquete.h"
#include "ecraninventaire.h"
#include "ecranquetejoueur.h"
#include "ecrannom.h"
#include "ecranrecapitulatifnuit.h"
#include "ecranpremierejournee.h"

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
