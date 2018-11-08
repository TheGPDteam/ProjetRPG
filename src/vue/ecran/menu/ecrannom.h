#ifndef ECRANNOM_H
#define ECRANNOM_H


#include "../ecrangeneral.h"
#include "../../interfaceutilisateur/saisir.h"
#include "../../interfaceutilisateur/conteneur/bouton/constantesbouton.h"
#include "../../outilsvue.h"

class EcranNom : public EcranGeneral {
private:
    TexteSDL m_nom_fenetre;
    TexteSDL m_label;
    Saisir* m_s;

public:
    EcranNom(Controleur *controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    void obtenirChangement(Observable &obj) override;

    ~EcranNom();
};
#endif // ECRANNOM_H
