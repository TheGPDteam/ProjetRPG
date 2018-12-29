#ifndef ECRANEQUIPE_H
#define ECRANEQUIPE_H

#include "tableaudefilable.h"
#include "ecrangeneral.h"

class EcranEquipe : public EcranGeneral
{

private :

//    TexteSDL m_nomFenetre;

    TableauDefilable * m_tableau_equipe;

    SDL_Rect m_rectangleHaut;
    SDL_Rect m_rectangleBas;
    SDL_Rect m_rectangleDescription;


    // Champ à compléter + intégration
    // Taille équipe ?
    //
//    TexteSDL* m_zoneNomPersonnage;
//    TexteSDL* m_zoneNiveauPersonnage;
//    TexteSDL* m_zoneViePersonnage;
//    TexteSDL* m_zoneIntelligencePersonnage;
//    TexteSDL* m_zoneForcePersonnage;
//    TexteSDL* m_zoneVitessePersonnage;

   // std::vector< TexteSDL* > m_vecteurPersonnagePourAffichage;

//    int m_idPersonnageSelectionne;


public:
    EcranEquipe(Controleur *controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    ~EcranEquipe();

    void obtenirChangement(Observable &obj) override;
};

#endif // ECRANEQUIPE_H
