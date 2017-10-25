#include "ecranquetejoueur.h"
#include "constantesbouton.h"
#include "bouton.h"
#include <utility>

EcranQueteJoueur::EcranQueteJoueur() : m_methodeVerificationCliqueSourisSurBouton(&DictionnaireDeBoutons::verificationCliqueSourisSurBouton),
    m_nomFenetre("Que Voulez vous faire ?", SDL_Color{255,255,255}, POLICE_COLLEGED, 20,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE-HEIGHT_BOUTON_NORMAL))
{
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL)-15, (HEIGHT_FENETRE_PRINCIPALE/2));
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Recolte", POLICE_COLLEGED, 20, coordB, tailleB), &ActionsBoutons::boutonJeuPrincipal);

    coordB = {(WIDTH_FENETRE_PRINCIPALE/2)+15, (HEIGHT_FENETRE_PRINCIPALE/2)};

    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Chasse", POLICE_COLLEGED, 20, coordB, tailleB), &ActionsBoutons::boutonJeuPrincipal);

    int x = (WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL)-30;
    int y = (HEIGHT_FENETRE_PRINCIPALE/2)-HEIGHT_BOUTON_NORMAL-15;

    m_fond = {x,y,WIDTH_FENETRE_PRINCIPALE-x*2,HEIGHT_FENETRE_PRINCIPALE-y*2};
    m_bordure = {m_fond.x-2,m_fond.y-2,m_fond.w+4,m_fond.h+4};

}

EcranQueteJoueur::~EcranQueteJoueur(){}

void EcranQueteJoueur::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage){
    SDL_FillRect(fenetre_affichage, &m_bordure, SDL_MapRGB(fenetre_affichage->format, 75, 75, 75));
    SDL_FillRect(fenetre_affichage, &m_fond, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));
    m_nomFenetre.afficherTexte(fenetre_affichage);
    afficherBoutons(coord_souris, fenetre_affichage);
}

void EcranQueteJoueur::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris){
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

void EcranQueteJoueur::obtenirChangement(Observable &obj){}
