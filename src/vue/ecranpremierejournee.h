#ifndef ECRANPREMIEREJOURNEE_H
#define ECRANPREMIEREJOURNEE_H

#include "ecrangeneral.h"

#include <string.h>

class EcranPremiereJournee : public EcranGeneral
{
private:
    const int DECALAGE_FOND_RECAP_NUIT = 100;
    const std::string CHEMIN_HISTOIRE = "./../rsc/histoire/histoire.txt";

    SDL_Rect m_fondRecapitulatif;

    std::vector< TexteSDL* > m_zoneHistoire;

    void recupererHistoire();

public:
    EcranPremiereJournee(Controleur *controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    void obtenirChangement(Observable &obj) override;

    ~EcranPremiereJournee();
};

#endif // ECRANPREMIEREJOURNEE_H
