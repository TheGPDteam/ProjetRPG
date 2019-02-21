#ifndef ECRANJEUPRINCIPAL_H
#define ECRANJEUPRINCIPAL_H

#include "ecrangeneral.h"
#include "carte.h"
#include "bouton.h"
#include "sauvegarde.h"
#include "tableaudefilable.h"
#include "temps.h"
#include "spritepersonnage.h"

class EcranJeuPrincipal : public EcranGeneral
{
private:
    static int const TAILLE_CARTE_AFFICHAGE=12;
    int const DECALAGE_CARTE_Y_SUPERIEUR=12;
    int const DECALAGE_CARTE_X_INFERIEUR=0;
    int const DECALAGE_CARTE_Y_INFERIEUR=0;
    int const DECALAGE_CARTE_X_SUPERIEUR=12;

    SpritePersonnage* m_spriteJoueur;
    std::array<std::array<Sprite*,TAILLE_CARTE_AFFICHAGE>,TAILLE_CARTE_AFFICHAGE> m_spritesCarte;
    std::set<Sprite*> m_spriteObjets;
    Carte* m_carte;

    TexteSDL m_objectif;
    TexteSDL m_nomJoueur;
    TexteSDL m_tempsRestant;



public:
    EcranJeuPrincipal(Controleur *controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;
    ~EcranJeuPrincipal() override;
    void obtenirChangement(Observable &obj) override;
    void definirCarte(Carte* carte);
};

#endif // ECRANJEUPRINCIPAL_H
