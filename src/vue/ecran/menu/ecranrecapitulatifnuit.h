#ifndef ECRANRECAPITULATIFNUIT_H
#define ECRANRECAPITULATIFNUIT_H

#include "ecrangeneral.h"
#include "textesdl.h"

class EcranRecapitulatifNuit : public EcranGeneral
{
private:
    const int DECALAGE_FOND_RECAP_NUIT = 100;
    const static int NB_DONNEES_NUIT = 3;
    const std::string CHEMIN_RECAP_NUIT = "./../rsc/recapNuits/recap.txt";

    const std::string TEXTE_ZOMBIES_TUES = "Nombre de zombies tues dans la journee : ";
    const std::string TEXTE_ZOMBIES_ATTAQUANT = "Nombre de zombies attaquants : ";
    const std::string TEXTE_HUMAINS_TUES = "Nombre de morts dans le camp : ";
    const std::string TEXTE_VIVRES_CONSOMMES = "Nombre de vivres consommes : ";

    const std::string TEXTE_GAME_OVER = "Vous avez perdu";
    const std::string TEXTE_GAME_OVER_FAMINE = "Vous ne pouvez assumer la consommation de votre camp";
    const std::string TEXTE_GAME_OVER_ATTAQUE_MORTELLE = "Les zombies etaient trop forts pour vous";
    const std::string TEXTE_GAME_OVER_COMBAT = "Vous avez peri en affrontant un groupe de zombies";
    const std::string TEXT_GAME_VICTORY = "Bravo !!! La fin d'Hitler est proche ...";


    SDL_Rect m_fondRecapitulatif;

    TexteSDL* m_zoneNombreZombiesTues;

    TexteSDL* m_zoneNombreZombiesAttaquants;

    TexteSDL* m_zoneNombreHumainsTues;

    TexteSDL* m_zoneVivresConsommes;

    TexteSDL* m_zoneGameOver;

    void recuperationDonneesDeLaJournee();
public:
    EcranRecapitulatifNuit(Controleur *controleur, GestionnaireRessource* gestionnaireRessource);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    void obtenirChangement(Observable &obj) override;

    ~EcranRecapitulatifNuit();
};

#endif // ECRANRECAPITULATIFNUIT_H
