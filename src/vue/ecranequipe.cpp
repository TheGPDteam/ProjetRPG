#include "ecranequipe.h"
#include "bouton.h"
#include "constantesbouton.h"
#include <utility>

// a déclarer autre part
const int COORD_X_RECTANGLE_HAUT = 20;
const int COORD_Y_RECTANGLE_HAUT = 50;

EcranEquipe::EcranEquipe() :
    m_nomFenetre("Equipe", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 60)),
    m_rectangleHaut {COORD_X_RECTANGLE_HAUT, COORD_Y_RECTANGLE_HAUT, WIDTH_FENETRE_PRINCIPALE - COORD_X_RECTANGLE_HAUT * 2, HEIGHT_FENETRE_PRINCIPALE - 250},
//    m_rectangleNomEquipe  {COORD_X_RECTANGLE_HAUT, COORD_Y_RECTANGLE_HAUT, WIDTH_FENETRE_PRINCIPALE - COORD_X_RECTANGLE_HAUT * 2, HEIGHT_FENETRE_PRINCIPALE - 250},,
    m_rectangleBas {COORD_X_RECTANGLE_HAUT, 10 + (50 + HEIGHT_FENETRE_PRINCIPALE - 250), WIDTH_FENETRE_PRINCIPALE - COORD_X_RECTANGLE_HAUT * 2, (HEIGHT_FENETRE_PRINCIPALE - (HEIGHT_FENETRE_PRINCIPALE - 250)) - 80},
    m_rectangleDescription {COORD_X_RECTANGLE_HAUT + 10, COORD_Y_RECTANGLE_HAUT + 10, WIDTH_FENETRE_PRINCIPALE - COORD_X_RECTANGLE_HAUT * 3, 40},
    m_zoneNomPersonnage {new TexteSDL("Nom", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleDescription.x + 10, m_rectangleDescription.y + 10))},
    m_zoneNiveauPersonnage {new TexteSDL("Niveau", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleDescription.x + 90, m_rectangleDescription.y + 10))},
    m_zoneViePersonnage {new TexteSDL("Vie", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleDescription.x + 210, m_rectangleDescription.y + 10))},           // position imprécise **
    m_zoneIntelligencePersonnage {new TexteSDL("Intelligence", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleDescription.x + 290, m_rectangleDescription.y + 10))},
    m_zoneForcePersonnage {new TexteSDL("Force", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleDescription.x + 510, m_rectangleDescription.y + 10))},
    m_zoneVitessePersonnage {new TexteSDL("Vitesse", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleDescription.x + 630, m_rectangleDescription.y + 10))}
{
    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Quitter", POLICE_COLLEGED, 20, std::make_pair(WIDTH_FENETRE_PRINCIPALE - 290, m_rectangleBas.y + 10), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL)), &ActionsBoutons::boutonJeuPrincipal);
}


//!
//! \brief Affiche l'ecran equipe
//! \author pgutierrez
//! @param fenetre_affichage fenetre dans laquelle l'objet s'affichera
//! \date 25/01/17
//! \version 0.1
//!
//! Affiche tout les éléments de l'écran equipe
//!


void EcranEquipe::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage)
{

    // SEule ligne de base : SDL_FillRect(fenetre_affichage, &fenetre_affichage->clip_rect, SDL_MapRGB(fenetre_affichage->format, 0, 0, 0));

    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
    SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));

    SDL_FillRect(fenetre_affichage, &m_rectangleHaut, SDL_MapRGB(fenetre_affichage->format, 100, 100, 100));
    SDL_FillRect(fenetre_affichage, &m_rectangleBas, SDL_MapRGB(fenetre_affichage->format, 100, 100, 100));
    SDL_FillRect(fenetre_affichage, &m_rectangleDescription, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));

    m_nomFenetre.afficherTexte(fenetre_affichage);
    m_zoneNomPersonnage->afficherTexte(fenetre_affichage);
    m_zoneNiveauPersonnage->afficherTexte(fenetre_affichage);
    m_zoneViePersonnage->afficherTexte(fenetre_affichage);
    m_zoneIntelligencePersonnage->afficherTexte(fenetre_affichage);
    m_zoneForcePersonnage->afficherTexte(fenetre_affichage);
    m_zoneVitessePersonnage->afficherTexte(fenetre_affichage);


     afficherBoutons(coord_souris, fenetre_affichage);

}


//!
//! \brief Gère les évènements
//! \author pgutierrez
//! @param controleur repésente le controleur de l'architecture MVC
//! @param quitter_jeu booléan représentant le fait de quitter le jeu ou non
//! @param clique_souris représente si la souris a reçu un clique en évènement
//! @param coord_souris représente les coordonnées de la souris
//! \date 25/01/17
//! \version 0.1
//!
//! Gère les évènements de cet écran
//!

void EcranEquipe::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris)
{
    SDL_Event evenements;

    while(SDL_PollEvent(&evenements))
    {
        switch(evenements.type)
        {
        case SDL_QUIT:
            quitter_jeu = true;
            SDL_Quit();
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


//!
//! \brief  Destructeur de l'ecran equipe
//! \author pgutierrez
//! \date 25/01/17
//! \version 1.0
//!
//! Détruit tout les élément de l'ecran equipe
//!

EcranEquipe::~EcranEquipe()
{
    if(m_zoneNomPersonnage != nullptr)
    {
        delete m_zoneNomPersonnage;
    }
}



void EcranEquipe::obtenirChangement(Observable &obj){

}
