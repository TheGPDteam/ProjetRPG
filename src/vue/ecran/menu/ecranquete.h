#ifndef CHOIXQUETE_H
#define CHOIXQUETE_H

#include "ecrangeneral.h"
#include "tableau.h"
#include "ecranrepartitionjoueur.h"
#include <map>

#define MARGE_ENTRE_FICHES 30
#define NOMBRE_DE_FICHES 3
#define MARGE_RECOLTE_CHASSE_CAMPEMENT (NOMBRE_DE_FICHES * MARGE_ENTRE_FICHES)/(NOMBRE_DE_FICHES+1)

class EcranQuete : public EcranGeneral
{
private:
    std::function<TypeEcran(DictionnaireDeBoutons&, std::pair<int, int> coord_souris, TypeEcran)> m_methodeVerificationCliqueSourisSurBouton;

    TexteSDL m_nomFenetre;
    bool m_afficherEcranRepartition=false;

    SDL_Rect m_fondChasse;
    SDL_Rect m_fondRecolte;
    SDL_Rect m_fondCampement;
    SDL_Rect m_fondPerso;
    SDL_Rect m_fondDescriptionPerso;

    Tableau * m_tableauNonAffectes;
    Tableau * m_tableauRecolte;
    Tableau * m_tableauChasse;
    Tableau * m_tableauCampement;
    std::map<Tableau *, Equipe *> m_tableaux;
    EcranRepartitionJoueur * m_ecranRepartitionJoueur;
public:
    EcranQuete(Controleur *controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    ~EcranQuete();

    void obtenirChangement(Observable &obj) override;
};
#endif // CHOIXQUETE_H

