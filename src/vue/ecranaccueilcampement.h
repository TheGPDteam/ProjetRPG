#ifndef ECRANACCUEILCAMPEMENT_H
#define ECRANACCUEILCAMPEMENT_H

#include "ecrangeneral.h"

class EcranAccueilCampement : public EcranGeneral
{
private:
    TexteSDL m_nomFenetre;
public:
    EcranAccueilCampement(Controleur* controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    ~EcranAccueilCampement();

    void obtenirChangement(Observable &obj) override;


};

#endif // ECRANACCUEILCAMPEMENT_H
