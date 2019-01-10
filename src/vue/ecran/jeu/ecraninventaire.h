#ifndef ECRANINVENTAIRE_H
#define ECRANINVENTAIRE_H

#include "tableaudefilable.h"
#include "zonedefilable.h"
#include "ecrangeneral.h"

#include <vector>

class EcranInventaire : public EcranGeneral
{
private:
    TexteSDL m_nomFenetre;
    TableauDefilable * m_tableau_objets;
    int m_compteurInventaire;

    SDL_Rect m_fondEcran;

    TexteSDL* m_quantiteInventaire;

    int m_idObjetSelectionne;

public:
    EcranInventaire(Controleur *controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    ~EcranInventaire();

    void obtenirChangement(Observable &obj) override;

    void definirEtatQuantite(Inventaire * inventaireJ);
    bool definirObjetPourAffichage(std::vector<Objet *> objets);
};

#endif // ECRANINVENTAIRE_H
