#ifndef ECRANREPARTITIONJOUEUR_H
#define ECRANREPARTITIONJOUEUR_H

#include "../ecrangeneral.h"

enum AFFECTATION {RETOUR, RIEN, CHASSE, RECOLTE, CAMPEMENT, NON_AFFECTE};

class EcranRepartitionJoueur : public EcranGeneral{


private:

    Controleur * m_controleur;

    SDL_Rect m_rectangleFichePersonnage;
    Humain * m_humain;

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
    bool m_etatAfficher;
    void gestionRepartion(AFFECTATION affectation);

public:

    EcranRepartitionJoueur(Controleur * controleur);
    void definirHumain(Humain * humain);
    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;
    bool obtenirEtatAfficher();
    int affecter();

    ~EcranRepartitionJoueur();
    void obtenirChangement(Observable &obj) override;
};

#endif // ECRANREPARTITIONJOUEUR_H
