#include "ecranmenuprincipal.h"
#include "constantesbouton.h"
#include "outilsvue.h"

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
    m_methodeVerificationCliqueSourisSurBouton(&DictionnaireDeBoutons::verificationCliqueSourisSurBoutons)
{
    SDL_Rect rect = {(WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2),  (HEIGHT_FENETRE_PRINCIPALE/2)-(HEIGHT_BOUTON_NORMAL/2)+ 100, WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL};
    ajoutBoutonDansMapDeBoutons(new Bouton("Nouvelle Partie", rect, m_controleur, nullptr, true, POLICE_COLLEGED), &ActionsBoutons::boutonNouvellePartie);

    rect.y += 70;
    bool chargementPossible = Sauvegarde::fichierSauvegardeExiste();
    ajoutBoutonDansMapDeBoutons(new Bouton("Continuer", rect, m_controleur, nullptr,
                                           chargementPossible, POLICE_COLLEGED), &ActionsBoutons::boutonChargement);

    rect.y += 70;
    ajoutBoutonDansMapDeBoutons(new Bouton("Quitter", rect, m_controleur, nullptr, true, POLICE_COLLEGED), &ActionsBoutons::boutonQuitter);

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


void EcranMenuPrincipal::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage){
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

void EcranMenuPrincipal::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris){
    SDL_Event evenements;

    while (SDL_PollEvent(&evenements)){
        switch (evenements.type){
        case SDL_QUIT:
            quitter_jeu = true;
            SDL_Quit();
            break;

        case SDL_MOUSEBUTTONUP:
            if (evenements.button.button == SDL_BUTTON_LEFT){
                clique_souris = true;
                coord_souris.first = evenements.button.x;
                coord_souris.second = evenements.button.y;
            }
            break;
        default:
            if(DictionnaireDeBoutons::boutonValiderEntree("Nouvelle Partie",evenements,clique_souris,coord_souris)) break;
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

EcranMenuPrincipal::~EcranMenuPrincipal(){

}

void EcranMenuPrincipal::obtenirChangement(Observable &obj){

}
