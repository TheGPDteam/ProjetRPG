#ifndef AFFICHEURZONE_H
#define AFFICHEURZONE_H

#include "carte.h"
#include "joueur.h"
#include "outilsvue.h"
#include "spritepersonnage.h"

class AfficheurZone {
private:
    static int const DECALAGE_CARTE_Y_SUPERIEUR = 11;
    static int const DECALAGE_CARTE_X_INFERIEUR = 0;
    static int const DECALAGE_CARTE_Y_INFERIEUR = 0;
    static int const DECALAGE_CARTE_X_SUPERIEUR = 19;
    static int const LARGEUR = 19;
    static int const HAUTEUR = 11;

    std::array<std::array<Sprite*, HAUTEUR>, LARGEUR> m_spritesCarte;
    std::set<Sprite*> m_spriteObjets;
    std::set<Sprite*> m_spriteZombies;
    SpritePersonnage* m_spriteJoueur;

    std::vector<int> calculerDecalageBord(int positionX, int positionY, int largeur_zone, int hauteur_zone);
public:
    AfficheurZone();
    ~AfficheurZone();

    SpritePersonnage* obtenirSpritePersonnage();
    void mettreAJour(Carte* carte, Joueur * joueur);
    void afficher(SDL_Surface *fenetre_affichage);
};

#endif // AFFICHEURZONE_H
