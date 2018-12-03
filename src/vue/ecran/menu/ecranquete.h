#ifndef CHOIXQUETE_H
#define CHOIXQUETE_H

#include "ecrangeneral.h"

#define MARGE_ENTRE_FICHES 30
#define NOMBRE_DE_FICHES 3
#define MARGE_RECOLTE_CHASSE_CAMPEMENT (NOMBRE_DE_FICHES * MARGE_ENTRE_FICHES)/(NOMBRE_DE_FICHES+1)

class EcranQuete : public EcranGeneral
{
private:
    std::function<TypeEcran(DictionnaireDeBoutons&, std::pair<int, int> coord_souris, TypeEcran)> m_methodeVerificationCliqueSourisSurBouton;

    TexteSDL m_nomFenetre;
    TexteSDL m_titreRecolte;
    TexteSDL m_titreChasse;
    TexteSDL m_titreCampement;

    Humain * m_humain_a_affecter;

    SDL_Rect m_fondChasse;
    SDL_Rect m_fondRecolte;
    SDL_Rect m_fondCampement;
    SDL_Rect m_fondPerso;
    SDL_Rect m_fondDescriptionPerso;
    SDL_Rect m_fondDescriptionChasse;
    SDL_Rect m_fondDescriptionRecolte;
    SDL_Rect m_fondDescriptionCampement;

    TexteSDL* m_zoneRecolte;
    TexteSDL* m_zoneChasse;
    TexteSDL* m_zoneCampement;
    TexteSDL* m_zoneNomPersonnage;
    TexteSDL* m_zonePrenomPersonnage;
    TexteSDL* m_zoneChassePersonnage;
    TexteSDL* m_zoneRecoltePersonnage;
    TexteSDL* m_zoneCampementPersonnage;
    TexteSDL* m_zoneForcePersonnage;
    TexteSDL* m_zoneVitessePersonnage;

    std::pair<int, int>m_CoordNom;
    std::pair<int, int>m_CoordPrenom;
    std::pair<int, int>m_CoordChasse;
    std::pair<int, int>m_CoordRecolte;
    std::pair<int, int>m_CoordCampement;
    std::pair<int, int>m_CoordForce;
    std::pair<int, int>m_CoordVitesse;
public:
    EcranQuete(Controleur *controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    ~EcranQuete();

    void obtenirChangement(Observable &obj) override;
};
#endif // CHOIXQUETE_H

