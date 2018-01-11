#ifndef ECRANQUETEJOUEUR_H
#define ECRANQUETEJOUEUR_H

#include "ecrangeneral.h"

class EcranQueteJoueur : public EcranGeneral
{
private:

    std::function<TypeEcran(DictionnaireDeBoutons&, std::pair<int, int> coord_souris, TypeEcran)> m_methodeVerificationCliqueSourisSurBouton;

    TexteSDL m_nomFenetre;

    SDL_Rect m_fond;
    SDL_Rect m_bordure;

public:
    EcranQueteJoueur(Controleur *controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    ~EcranQueteJoueur();

    void obtenirChangement(Observable &obj) override;

};

#endif // ECRANQUETEJOUEUR_H
