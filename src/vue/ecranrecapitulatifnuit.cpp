#include "ecranrecapitulatifnuit.h"
#include "constantesbouton.h"

#include <fstream>

//! TODO: Rajouter un bouton (croix ou "Suivant") pour passer l'écran.
//! A lier avec le cycle jour nuit.

//!
//! \brief Constructeur pour l'ecran de recapitulatif durant la nuit
//! \author pgutierrez
//! \date 13/11/17
//! \version 1.0
//!

EcranRecapitulatifNuit::EcranRecapitulatifNuit(Controleur* controleur)
    : EcranGeneral{controleur}
{
    short unsigned int largeurFond, hauteurFond;
    largeurFond = WIDTH_FENETRE_PRINCIPALE - 2*DECALAGE_FOND_RECAP_NUIT;
    hauteurFond = HEIGHT_FENETRE_PRINCIPALE - 2*DECALAGE_FOND_RECAP_NUIT;

    m_fondRecapitulatif = {(short int)DECALAGE_FOND_RECAP_NUIT, (short int)DECALAGE_FOND_RECAP_NUIT, largeurFond, hauteurFond};
    m_zoneNombreZombiesTues = new TexteSDL(TEXTE_ZOMBIES_TUES + std::to_string(m_controleur->obtenirModele()->obtenirNbZombiesTues()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_fondRecapitulatif.x + 15, m_fondRecapitulatif.y + 15));
    m_zoneNombreZombiesAttaquants = new TexteSDL(TEXTE_ZOMBIES_ATTAQUANT + std::to_string(m_controleur->obtenirModele()->obtenirNbZombiesAttaquants()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_fondRecapitulatif.x + 15, m_fondRecapitulatif.y + 165));
    m_zoneNombreHumainsTues = new TexteSDL(TEXTE_HUMAINS_TUES + std::to_string(m_controleur->obtenirModele()->obtenirNbPersosMorts()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_fondRecapitulatif.x + 15, m_fondRecapitulatif.y + 315));
    m_zoneGameOver = new TexteSDL(TEXTE_GAME_OVER, SDL_Color{0,0,0,255}, POLICE_COLLEGED, 30, std::make_pair(m_fondRecapitulatif.x + 250, m_fondRecapitulatif.y + 200));

    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Suivant", POLICE_COLLEGED, 20,
                                           std::make_pair(DECALAGE_FOND_RECAP_NUIT + 300, DECALAGE_FOND_RECAP_NUIT + hauteurFond - 100),
                                           std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL),
                                           std::make_pair(DECALAGE_FOND_RECAP_NUIT + 310, DECALAGE_FOND_RECAP_NUIT + hauteurFond - 90)),
                                &ActionsBoutons::boutonChoixPersonnageCycle);

    // Cette ligne permet de tester la recuperation de donnée dans le fichier.
    recuperationDonneesDeLaJournee();
}



//!
//! \brief Récupère les valeurs dans un fichier
//! \author pgutierrez
//! \date 13/11/17
//! \version 1.0
//! Un fichier contient toutes les données pour le récapitulatif
//!

void EcranRecapitulatifNuit::recuperationDonneesDeLaJournee()
{
//    std::ifstream fichier(CHEMIN_RECAP_NUIT, std::ifstream::in);

//    std::string tabValeurs[NB_DONNEES_NUIT];
//    std::string tmpString;

//    if(fichier.good())
//    {
//        for (int cpt = 0; cpt < NB_DONNEES_NUIT; ++cpt)
//        {
//            fichier >> tmpString;
//            tabValeurs[cpt] = tmpString;
//        }

//        fichier.close();

        m_zoneNombreZombiesTues->mettreAJourTexte(TEXTE_ZOMBIES_TUES + std::to_string(m_controleur->obtenirModele()->obtenirNbZombiesTues()));
        m_zoneNombreZombiesAttaquants->mettreAJourTexte(TEXTE_ZOMBIES_ATTAQUANT + std::to_string(m_controleur->obtenirModele()->obtenirNbZombiesAttaquants()));
        m_zoneNombreHumainsTues->mettreAJourTexte(TEXTE_HUMAINS_TUES + std::to_string(m_controleur->obtenirModele()->obtenirNbPersosMorts()));
//    }
}



//!
//! \brief Récupère les valeurs dans un fichier
//! \author pgutierrez
//! \date 13/11/17
//! \version 1.0
//! Un fichier contient toutes les données pour le récapitulatif
//!

void EcranRecapitulatifNuit::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage)
{
    SDL_FillRect(fenetre_affichage, &m_fondRecapitulatif, SDL_MapRGB(fenetre_affichage->format, 100, 100, 100));

    recuperationDonneesDeLaJournee();

    m_zoneNombreZombiesTues->afficherTexte(fenetre_affichage);
    m_zoneNombreZombiesAttaquants->afficherTexte(fenetre_affichage);
    m_zoneNombreHumainsTues->afficherTexte(fenetre_affichage);

    if (m_controleur->obtenirModele()->perdu())
    {
        //afficher un fond pour mieux voir le message (pop-up?/nouvel ecran ? )

        m_zoneGameOver->afficherTexte(fenetre_affichage);
        switch (m_controleur->obtenirModele()->obtenirTypeDefaite())
        {
        case TypeDefaite::FAMINE:
        {
            TexteSDL m_zoneGameOverFamine = TexteSDL(TEXTE_GAME_OVER_FAMINE, SDL_Color{0,0,0,255}, POLICE_COLLEGED, 19, std::make_pair(m_fondRecapitulatif.x + 25, m_fondRecapitulatif.y + 250));
            m_zoneGameOverFamine.afficherTexte(fenetre_affichage);
            break;
        }
        case TypeDefaite::ATTAQUEZOMBIES:
        {
            TexteSDL m_zoneGameOverAttaqueZombie = TexteSDL(TEXTE_GAME_OVER_ATTAQUE_MORTELLE, SDL_Color{0,0,0,255}, POLICE_COLLEGED, 19, std::make_pair(m_fondRecapitulatif.x + 15, m_fondRecapitulatif.y + 250));
            m_zoneGameOverAttaqueZombie.afficherTexte(fenetre_affichage);
            break;
        }
        default:
            break;
        }

        //Afficher un bouton pour recommencer
    }


    afficherBoutons(coord_souris, fenetre_affichage);
}



//!
//! \brief Gère les évènements
//! \author pgutierrez
//! @param controleur repésente le controleur de l'architecture MVC
//! @param quitter_jeu booléan représentant le fait de quitter le jeu ou non
//! @param clique_souris représente si la souris a reçu un clique en évènement
//! @param coord_souris représente les coordonnées de la souris
//! \date 13/11/17
//! \version 0.1
//!
//! Gère les évènements de cet écran
//!

void EcranRecapitulatifNuit::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris)
{
    SDL_Event evenements;

    while(SDL_PollEvent(&evenements))
    {
        switch(evenements.type)
        {
        case SDL_QUIT:
            quitter_jeu = true;
            break;

        case SDL_MOUSEBUTTONUP:
            if(evenements.button.button == SDL_BUTTON_LEFT)
            {
                clique_souris = true;
                coord_souris.first = evenements.button.x;
                coord_souris.second = evenements.button.y;
            }
            break;
        default:
            coord_souris.first = evenements.button.x;
            coord_souris.second = evenements.button.y;
            break;
        }
    }
}



void EcranRecapitulatifNuit::obtenirChangement(Observable &obj)
{
    //TODO: Définir l'objet permettant d'obtenir le changement et d'utiliser recuperationDonneesDeLaJournee
}



//!
//! \brief  Destructeur de l'écran recapitulatif
//! \author pgutierrez
//! \date 13/11/17
//! \version 1.0
//!
//! Détruit tous les éléments de l'écran recapitulatif
//!

EcranRecapitulatifNuit::~EcranRecapitulatifNuit()
{
    if (m_zoneNombreZombiesTues != nullptr)
    {
        delete m_zoneNombreZombiesTues;
    }

    if (m_zoneNombreZombiesAttaquants != nullptr)
    {
        delete m_zoneNombreZombiesAttaquants;
    }

    if (m_zoneNombreHumainsTues != nullptr)
    {
        delete m_zoneNombreHumainsTues;
    }
}
