#ifndef ECRANJEUPRINCIPAL_H
#define ECRANJEUPRINCIPAL_H

#include "ecrangeneral.h"
#include "modele/carte.h"
#include "vue/bouton.h"
#include "save/sauvegarde.h"


class EcranJeuPrincipal : public EcranGeneral
{
private:
    static int const TAILLE_CARTE_AFFICHAGE=12;
    int const DECALAGE_CARTE_Y_SUPERIEUR=12;
    int const DECALAGE_CARTE_X_INFERIEUR=0;
    int const DECALAGE_CARTE_Y_INFERIEUR=0;
    int const DECALAGE_CARTE_X_SUPERIEUR=12;

    Sprite* m_spriteJoueur;
    std::array<std::array<Sprite*,TAILLE_CARTE_AFFICHAGE>,TAILLE_CARTE_AFFICHAGE> m_spritesCarte;
    std::set<std::pair<short,short> > m_spriteObjets;
    Carte* m_carte;

    TexteSDL m_texteObjectif;
    TexteSDL m_objectif;
    TexteSDL m_nomJoueur;
    TexteSDL m_tempsRestant;

//    Controleur* m_controleur;

public:
    EcranJeuPrincipal(Controleur *controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;
    ~EcranJeuPrincipal();

    void obtenirChangement(Observable &obj) override;
    void definirCarte(Carte* carte);
};

#endif // ECRANJEUPRINCIPAL_H
