#ifndef AFFICHEURZONE_H
#define AFFICHEURZONE_H

#include "carte.h"
#include "joueur.h"
#include "outilsvue.h"

class AfficheurZone {
private:
    static int const DECALAGE_CARTE_Y_SUPERIEUR = 11;
    static int const DECALAGE_CARTE_X_INFERIEUR = 0;
    static int const DECALAGE_CARTE_Y_INFERIEUR = 0;
    static int const DECALAGE_CARTE_X_SUPERIEUR = 13;

    std::array<std::array<Sprite*, DECALAGE_CARTE_Y_SUPERIEUR>, DECALAGE_CARTE_X_SUPERIEUR> m_spritesCarte;
    std::set<Sprite*> m_spriteObjets;

public:
    AfficheurZone();
    ~AfficheurZone();
    void mettreAJour(Carte* carte, Joueur * joueur, bool joueur_provoque_changement);
    void afficher(SDL_Surface *fenetre_affichage);
};

#endif // AFFICHEURZONE_H
