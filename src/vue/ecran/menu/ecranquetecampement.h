#ifndef ECRANQUETECAMPEMENT_H
#define ECRANQUETECAMPEMENT_H

#include "ecrangeneral.h"
#include "outilsvue.h"
#include "constantesbouton.h"
#include "tableau.h"


const int NB_ESSENCES =  4;
const int NB_ROUES = 4;
class EcranQueteCampement : public EcranGeneral
{
private:
    std::vector<SDL_Rect> m_emplacementRoues;
    //Sprite* m_spriteRoue;
    Sprite* m_spriteHuile;
    Sprite* m_spriteEssence;
    Sprite* m_spriteMoteur;
    Sprite* m_tabEssence[NB_ESSENCES];
    Sprite* m_tabRoue[NB_ROUES];
    Sprite* m_bus;
//    Tableau * m_tableauEquipe;
    TexteSDL* m_labelRoue;
    TexteSDL* m_labelHuile;
    TexteSDL* m_labelEssence;
    TexteSDL* m_labelMoteur;

    TexteSDL* m_jaugeHuile;
    TexteSDL* m_jaugeEssence;
    TexteSDL* m_nombreRoues;

    std::pair<int,int> coordBoutonCampement;
public:
    EcranQueteCampement(Controleur* controleur);

    void obtenirChangement(Observable &obj);
    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage);
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris);
};

#endif // ECRANQUETECAMPEMENT_H
