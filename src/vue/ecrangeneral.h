#ifndef ECRANGENERAL_H
#define ECRANGENERAL_H

#include "controleur/controleur.h"
#include "dictionnairedeboutons.h"
#include "observateur.h"
#include "policetexte.h"

class EcranGeneral : public DictionnaireDeBoutons, public Observateur
{
public:
    EcranGeneral();

    virtual void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage) = 0;
    virtual void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) = 0;

    virtual ~EcranGeneral();
};

#endif // ECRANGENERAL_H
