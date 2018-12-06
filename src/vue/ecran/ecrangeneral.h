#ifndef ECRANGENERAL_H
#define ECRANGENERAL_H

#include "controleur/controleur.h"
#include "../interfaceutilisateur/conteneur/bouton/dictionnairedeboutons.h"
#include "../../observateur.h"
#include "../interfaceutilisateur/ressources/policetexte.h"
#include "../outilsvue.h"

class EcranGeneral : public DictionnaireDeBoutons, public Observateur
{
protected :
    Controleur* m_controleur;
    SDL_Surface * m_fond;

    SDL_Rect m_ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
public:
    EcranGeneral(Controleur * controleur);

    void afficherFondEcran(SDL_Surface* fenetre_affichage);

    virtual void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage) = 0;
    virtual void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) = 0;

    virtual ~EcranGeneral();
};

#endif // ECRANGENERAL_H
