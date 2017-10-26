#ifndef CHOIXQUETE_H
#define CHOIXQUETE_H

#include "ecrangeneral.h"

class EcranQuete : public EcranGeneral
{
private:
    std::function<TypeEcran(DictionnaireDeBoutons&, std::pair<int, int> coord_souris, TypeEcran)> m_methodeVerificationCliqueSourisSurBouton;

    SDL_Rect m_fondChasse;
    SDL_Rect m_fondRecolte;
    SDL_Rect m_fondPerso;
    SDL_Rect m_fondDescriptionPerso;
    SDL_Rect m_fondDescriptionChasse;
    SDL_Rect m_fondDescriptionRecolte;

    TexteSDL m_nomFenetre;

    TexteSDL* m_zoneRecolte;
    TexteSDL* m_zoneChasse;
    TexteSDL* m_zoneNomPersonnage;
    TexteSDL* m_zoneNiveauPersonnage;
    TexteSDL* m_zoneViePersonnage;
    TexteSDL* m_zoneIntelligencePersonnage;
    TexteSDL* m_zoneForcePersonnage;
    TexteSDL* m_zoneVitessePersonnage;

public:
    EcranQuete();

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    ~EcranQuete();

    void obtenirChangement(Observable &obj) override;

};

#endif // CHOIXQUETE_H

