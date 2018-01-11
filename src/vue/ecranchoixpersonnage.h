#ifndef ECRANCHOIXPERSONNAGE_H
#define ECRANCHOIXPERSONNAGE_H

#endif // ECRANCHOIXPERSONNAGE_H

#include "ecrangeneral.h"

class EcranChoixPersonnage : public EcranGeneral{

private:

    TexteSDL m_nomFenetre;

  //  SDL_Rect m_fondEcran; ?.??

    SDL_Rect m_rectangleFichePersonnage;
    SDL_Rect m_rectangleBas;

    TexteSDL* m_zoneNomPersonnage;

    TexteSDL* m_zoneDescriptionPersonnage;

    TexteSDL* m_zoneImagePersonnage;
    TexteSDL* m_zoneStatistiquesPersonnage;
    TexteSDL* m_zoneNiveauPersonnage;

    TexteSDL* m_zoneQuestion;



public:

    EcranChoixPersonnage(Controleur *controleur);


    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    void obtenirChangement(Observable &obj) override;

    ~EcranChoixPersonnage();

};
