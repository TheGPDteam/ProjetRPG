#ifndef ECRANREPARTITIONJOUEUR_H
#define ECRANREPARTITIONJOUEUR_H

#include "../ecrangeneral.h"

enum AFFECTATION {RETOUR, RIEN, CHASSE, RECOLTE, CAMPEMENT};

class EcranRepartitionJoueur{


private:

    Controleur * m_controleur;

    SDL_Rect m_rectangleFichePersonnage;


    TexteSDL* m_zonePrenomPersonnage;
    TexteSDL* m_zoneNomPersonnage;

    TexteSDL* m_zoneForcePersonnage;
    TexteSDL* m_zoneIntelligencePersonnage;
    TexteSDL* m_zoneVitessePersonnage;

    TexteSDL* m_zoneChassePersonnage;
    TexteSDL* m_zoneRecoltePersonnage;
    TexteSDL* m_zoneCampementPersonnage;

    TexteSDL* m_zoneNiveauPersonnage;

    TexteSDL* m_zoneNomArmePersonnage;
    TexteSDL* m_zoneDescArmePersonnage;
    TexteSDL* m_zoneDegatsArmePersonnage;

    TexteSDL* m_zoneQuestion;

    Bouton * m_retour;
    Bouton * m_chasse;
    Bouton * m_recolte;
    Bouton * m_campement;

    SDL_Surface* m_fenetre;

    void afficher() ;
    int gestionDesEvenements() ;

public:

    EcranRepartitionJoueur(Humain * humain, SDL_Surface * fenetre, Controleur * controleur);


    int affecter();

    ~EcranRepartitionJoueur();
};

#endif // ECRANREPARTITIONJOUEUR_H
