#include "ecranquete.h"
#include "constantesbouton.h"

EcranQuete::EcranQuete() : m_methodeVerificationCliqueSourisSurBouton(&DictionnaireDeBoutons::verificationCliqueSourisSurBouton)
{
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/4)-(WIDTH_BOUTON_NORMAL/4), (HEIGHT_FENETRE_PRINCIPALE)-(HEIGHT_BOUTON_NORMAL)-10);
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Nouvelle Partie", POLICE_COLLEGED, 20, coordB, tailleB), &ActionsBoutons::boutonJeuPrincipal);

    coordB.first = (WIDTH_FENETRE_PRINCIPALE/4)-(WIDTH_BOUTON_NORMAL/4)+WIDTH_BOUTON_NORMAL+100;

    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Quitter", POLICE_COLLEGED, 30, coordB, tailleB), &ActionsBoutons::boutonQuitter);

    int Distance_Fond_Perso = 20;

    m_fondPerso = {Distance_Fond_Perso,Distance_Fond_Perso,WIDTH_FENETRE_PRINCIPALE-Distance_Fond_Perso*2,HEIGHT_FENETRE_PRINCIPALE/2-Distance_Fond_Perso*2};
}
EcranQuete::~EcranQuete(){}


void EcranQuete::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage)
{
    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
    SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));

    SDL_FillRect(fenetre_affichage, &m_fondPerso, SDL_MapRGB(fenetre_affichage->format, 100,100,100));

    afficherBoutons(coord_souris, fenetre_affichage);
}


void EcranQuete::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris)
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

void EcranQuete::obtenirChangement(Observable &obj){}
