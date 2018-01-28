#include "ecranaccueilcampement.h"
#include "bouton.h"
#include "constantesbouton.h"
#include <utility>

EcranAccueilCampement::EcranAccueilCampement(Controleur* controleur)
    :EcranGeneral{controleur},
      m_nomFenetre("Campement", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,
                   std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 60))

{
    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Retour jeu", POLICE_COLLEGED, 17, std::make_pair(WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE - 100), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL), std::make_pair(WIDTH_FENETRE_PRINCIPALE - 217, HEIGHT_FENETRE_PRINCIPALE - 73)), &ActionsBoutons::boutonJeuPrincipal);
}

void EcranAccueilCampement::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage)
{
    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
    SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));
    m_nomFenetre.afficherTexte(fenetre_affichage);

    afficherBoutons(coord_souris, fenetre_affichage);
}

void EcranAccueilCampement::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris)
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

EcranAccueilCampement::~EcranAccueilCampement()
{
}

void EcranAccueilCampement::obtenirChangement(Observable &obj)
{

}
