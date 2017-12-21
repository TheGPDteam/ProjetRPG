#ifndef ECRANNOM_H
#define ECRANNOM_H


#include "ecrangeneral.h"
#include "saisir.h"

class EcranNom : public EcranGeneral {
private:

    Saisir* s;
    TexteSDL m_nom_fenetre;

    TexteSDL m_label;

    bool estLettre(char* a);
public:
    EcranNom();

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    virtual ~EcranNom() = default;

    void obtenirChangement(Observable &obj) override;


};

#endif // ECRANNOM_H
