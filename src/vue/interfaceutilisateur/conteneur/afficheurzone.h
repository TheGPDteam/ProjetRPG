#ifndef AFFICHEURZONE_H
#define AFFICHEURZONE_H

#include "carte.h"
#include "joueur.h"
#include "outilsvue.h"

class AfficheurZone {
private:
    static int const TAILLE_CARTE_AFFICHAGE = 12;
    int const DECALAGE_CARTE_Y_SUPERIEUR = 12;
    int const DECALAGE_CARTE_X_INFERIEUR = 0;
    int const DECALAGE_CARTE_Y_INFERIEUR = 0;
    int const DECALAGE_CARTE_X_SUPERIEUR = 12;

    std::array<std::array<Sprite*,TAILLE_CARTE_AFFICHAGE>,TAILLE_CARTE_AFFICHAGE> m_spritesCarte;
    std::set<Sprite*> m_spriteObjets;

public:
    AfficheurZone();
    ~AfficheurZone();
    void mettreAJour(Carte* carte, Joueur * joueur, bool joueur_provoque_changement);
    void afficher(SDL_Surface *fenetre_affichage);
};

#endif // AFFICHEURZONE_H
