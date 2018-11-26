#ifndef ECRANQUETECAMPEMENT_H
#define ECRANQUETECAMPEMENT_H

#include "../ecrangeneral.h"
#include "../outilsvue.h"
#include "../../interfaceutilisateur/conteneur/bouton/constantesbouton.h"


class EcranQueteCampement : public EcranGeneral
{
private:
    std::vector<SDL_Rect> m_emplacementRoues;
    Sprite* m_spriteRoue;
    Sprite* m_spriteHuile;
    Sprite* m_spriteEssence;
    Sprite* m_spriteMoteur;
    std::pair<int,int> coordBoutonRetour;
    std::pair<int,int> coordBoutonCampement;
public:
    EcranQueteCampement(Controleur* controleur);

    void obtenirChangement(Observable &obj);
    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage);
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris);
};

#endif // ECRANQUETECAMPEMENT_H