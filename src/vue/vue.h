#ifndef vue_h
#define vue_h

#include "ecranmenuprincipal.h"
#include "ecranjeuprincipal.h"
#include "ecranequipe.h"
#include "ecranchoixpersonnage.h"
#include "ecraninventaire.h"
#include "controleur/controleur.h"
#include "ecranquete.h"

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
    EcranQuete* m_ChoixQuete;

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

    void changerEcran(TypeEcran nouvelEcran);

    bool getFermerJeu();

    ~Vue();
};

#endif
