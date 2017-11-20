#ifndef ECRANRECAPITULATIFNUIT_H
#define ECRANRECAPITULATIFNUIT_H

#include <fstream>
#include "ecrangeneral.h"
#include "textesdl.h"

class EcranRecapitulatifNuit : public EcranGeneral
{
private:
    const int DECALAGE_FOND_RECAP_NUIT = 100;
    const static int NB_DONNEES_NUIT = 3;
    const std::string CHEMIN_RECAP_NUIT = "./../rsc/recapNuits/recap.txt";

    const std::string TEXTE_ZOMBIES_TUES = "Nombre de zombies tues : ";
    const std::string TEXTE_ZOMBIES_ATTAQUANT = "Nombre de zombies attaquants : ";
    const std::string TEXTE_HUMAINS_TUES = "Nombre de morts dans le camp : ";

    SDL_Rect m_fondRecapitulatif;

    TexteSDL* m_zoneNombreZombiesTues;

    TexteSDL* m_zoneNombreZombiesAttaquants;

    TexteSDL* m_zoneNombreHumainsTues;

    void recuperationDonneesDeLaJournee();
public:
    EcranRecapitulatifNuit();

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    void obtenirChangement(Observable &obj) override;

    ~EcranRecapitulatifNuit();
};

#endif // ECRANRECAPITULATIFNUIT_H
