#ifndef ECRANJEUPRINCIPAL_H
#define ECRANJEUPRINCIPAL_H

#include "ecrangeneral.h"
#include "carte.h"
#include "bouton.h"
#include "sauvegarde.h"
#include "tableaudefilable.h"
#include "temps.h"
#include "spritepersonnage.h"
#include "afficheurzone.h"

class EcranJeuPrincipal : public EcranGeneral{
private:
    int const NB_ETAPES_ANIMATION = 15;

    SpritePersonnage* m_spriteJoueur;
    AfficheurZone m_afficheurZone;
    Carte* m_carte;

    TexteSDL m_objectif;
    TexteSDL m_nomJoueur;
    TexteSDL m_tempsRestant;
    void animerDeplacement(Joueur *joueur, SDL_Surface * ecran);
    Sprite * creerSpriteTuile(int tuileX, int tuileY, int posDessinX,  int posDessinY);
    Sprite * creerSpriteObjet(Joueur *joueur, int tuileX, int tuileY, int posDessinX, int posDessinY);
public:
    EcranJeuPrincipal(Controleur *controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;
    ~EcranJeuPrincipal() override;
    void obtenirChangement(Observable &obj) override;
    void definirCarte(Carte* carte);
};

#endif // ECRANJEUPRINCIPAL_H
