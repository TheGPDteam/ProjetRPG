#ifndef ECRANMENUPRINCIPAL_H
#define ECRANMENUPRINCIPAL_H

#include <SDL/SDL.h>
#include <utility>

#include "../observable.h"
#include "ecrangeneral.h"


class EcranMenuPrincipal : public EcranGeneral
{
private:
    std::function<TypeEcran(DictionnaireDeBoutons&, std::pair<int, int> coord_souris, TypeEcran)> m_methodeVerificationCliqueSourisSurBouton;
public:
    EcranMenuPrincipal(Controleur *controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    ~EcranMenuPrincipal();

    void obtenirChangement(Observable &obj) override;
};

#endif // ECRANMENUPRINCIPAL_H
