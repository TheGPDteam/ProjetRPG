#ifndef ECRANQUETECAMPEMENT_H
#define ECRANQUETECAMPEMENT_H

#include "ecrangeneral.h"
#include "outilsvue.h"
#include "constantesbouton.h"
#include "tableau.h"




class EcranQueteCampement : public EcranGeneral
{  
private:
    static const int NB_ESSENCES_MAX =  4;
    static const int NB_ROUES_MAX = 4;

    std::vector<SDL_Rect> m_emplacementRoues;
    Bouton m_bouton;

    Sprite* m_spriteHuile;
    Sprite* m_spriteMoteur;
    Sprite* m_tabEssence[NB_ESSENCES_MAX];
    Sprite* m_tabRoue[NB_ROUES_MAX];
    Sprite* m_bus;

    std::pair<int,int> coordBoutonCampement;
public:
    EcranQueteCampement(Controleur* controleur, GestionnaireRessource* gestionnaireRessource);

    void obtenirChangement(Observable &obj);
    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage);
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris);
};

#endif // ECRANQUETECAMPEMENT_H
