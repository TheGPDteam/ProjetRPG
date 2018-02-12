#ifndef ECRANLISTEOBJETS_H
#define ECRANLISTEOBJETS_H

#include "ecrangeneral.h"

class EcranListeObjet : public EcranGeneral
{
private:
    TexteSDL m_nomFenetre;

    TexteSDL m_nomObjet;
    TexteSDL m_descObjet;

    SDL_Rect m_rectangleFicheObjet;
public:
    EcranListeObjet(Controleur * controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    void obtenirChangement(Observable &obj) override;
};

#endif // ECRANLISTEOBJETS_H
