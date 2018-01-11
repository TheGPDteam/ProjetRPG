#ifndef ECRANINVENTAIRE_H
#define ECRANINVENTAIRE_H

#include "ecrangeneral.h"

#include <vector>

class EcranInventaire : public EcranGeneral
{
private:
    TexteSDL m_nomFenetre;

    int m_compteurInventaire;

    SDL_Rect m_fondEcran;
    SDL_Rect m_rectangleHaut;
    SDL_Rect m_rectangleBas;
    SDL_Rect m_rectangleDescription;

    TexteSDL* m_zoneNomObjet;
    TexteSDL* m_zoneDescriptionObjet;
    TexteSDL* m_quantiteInventaire;

    std::vector< std::vector< TexteSDL* > > m_vecteurObjetPourAffichage;

    int m_idObjetSelectionne;

public:
    EcranInventaire(Controleur *controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    ~EcranInventaire();

    void obtenirChangement(Observable &obj) override;

    void definirEtatQuantite(int quantite_objets);
    bool definirObjetPourAffichage(std::vector<Objet *> objets);
};

#endif // ECRANINVENTAIRE_H
