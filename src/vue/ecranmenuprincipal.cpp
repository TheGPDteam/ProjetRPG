#include "ecranmenuprincipal.h"
#include "constantesbouton.h"

//!
//! \brief Constructeur par défaut de l'écran de menu principal
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.2
//!
//! Initialise tout le contenu de l'écran principal de jeu
//!

EcranMenuPrincipal::EcranMenuPrincipal(Controleur* controleur) :
    EcranGeneral{controleur},
    m_methodeVerificationCliqueSourisSurBouton(&DictionnaireDeBoutons::verificationCliqueSourisSurBouton)
{
    //! A EFFACER*
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2), (HEIGHT_FENETRE_PRINCIPALE/2)-(HEIGHT_BOUTON_NORMAL/2));
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);


    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Nouvelle Partie", POLICE_COLLEGED, 17, coordB, tailleB,std::make_pair(coordB.first+20,coordB.second+15)), &ActionsBoutons::boutonNouvellePartie);

    coordB.first = (WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2);
    coordB.second = (HEIGHT_FENETRE_PRINCIPALE/2)-(HEIGHT_BOUTON_NORMAL/2) +100;

    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, false, "Continuer", POLICE_COLLEGED, 17, coordB, tailleB,std::make_pair(coordB.first+60,coordB.second+15)), &ActionsBoutons::boutonQuete);

        coordB.second = (HEIGHT_FENETRE_PRINCIPALE/2)-(HEIGHT_BOUTON_NORMAL/2) +200;

    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Quitter", POLICE_COLLEGED, 17, coordB, tailleB,std::make_pair(coordB.first+75,coordB.second+15)), &ActionsBoutons::boutonQuitter);
}


//!
//! \brief Affiche le menu principal
//! \author pgutierrez
//! @param fenetre_affichage fenetre dans laquelle l'objet s'affichera
//! \date 21/11/16
//! \version 0.1
//!
//! Affiche tout les éléments de l'écran du menu principal
//!


void EcranMenuPrincipal::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage)
{
//    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
//    //SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 255, 150, 150));
//    SDL_Surface* imageFond = SDL_LoadBMP("../rsc/sprites/ecran_titre.bmp");
//    SDL_BlitSurface(imageFond,new SDL_Rect{0,0,1024,668},fenetre_affichage,new SDL_Rect{0,0,0,0});
    afficherFondEcran(fenetre_affichage);
    afficherBoutons(coord_souris, fenetre_affichage);
}


//!
//! \brief Gère les évènements
//! \author pgutierrez
//! @param controleur repésente le controleur de l'architecture MVC
//! @param quitter_jeu booléan représentant le fait de quitter le jeu ou non
//! @param clique_souris représente si la souris a reçu un clique en évènement
//! @param coord_souris représente les coordonnées de la souris
//! \date 30/11/16
//! \version 0.1
//!
//! Gère les évènements de cet écran
//!

void EcranMenuPrincipal::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris)
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
//! \brief  Destructeur d'un menu principal
//! \author pgutierrez
//! \date 21/11/16
//! \version 1.0
//!
//! Détruit tout les élément d'une menu principal
//!

EcranMenuPrincipal::~EcranMenuPrincipal()
{

}

void EcranMenuPrincipal::obtenirChangement(Observable &obj){

}
