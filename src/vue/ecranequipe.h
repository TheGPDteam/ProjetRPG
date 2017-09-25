#ifndef ECRANEQUIPE_H
#define ECRANEQUIPE_H

#include "ecrangeneral.h"

class EcranEquipe : public EcranGeneral
{
public:
    EcranEquipe();

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    ~EcranEquipe();

    void obtenirChangement(Observable &obj) override;
};

#endif // ECRANEQUIPE_H
