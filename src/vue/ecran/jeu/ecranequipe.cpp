#include "ecranequipe.h"
#include "bouton.h"
#include "constantesbouton.h"
#include <utility>

// a déclarer autre part
const short COORD_X_RECTANGLE_HAUT = 20;
const short COORD_Y_RECTANGLE_HAUT = 50;

const int LARGEUR_TABLEAU = 0.7 * WIDTH_FENETRE_PRINCIPALE;
const int HAUTEUR_TABLEAU = 0.7 * HEIGHT_FENETRE_PRINCIPALE;


EcranEquipe::EcranEquipe(Controleur* controleur) :
    EcranGeneral{controleur}
   {
    SDL_Rect rect_tableau = {0.15*WIDTH_FENETRE_PRINCIPALE, 0.15*HEIGHT_FENETRE_PRINCIPALE, LARGEUR_TABLEAU,HAUTEUR_TABLEAU};
    m_tableau_equipe = TableauDefilable::tableauHumain(rect_tableau, controleur,"Equipe", false);

    const std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);
    SDL_Rect rect = {WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE-2*tailleB.second, tailleB.first, tailleB.second};
    ajoutBoutonDansMapDeBoutons(new Bouton("Retour jeu", rect, m_controleur, nullptr,
                                           true, POLICE_COLLEGED), &ActionsBoutons::boutonJeuPrincipal);
    obtenirChangement(*m_controleur->obtenirModele()->obtenirJoueur()->obtenirEquipe());
}


//!
//! \brief Affiche l'ecran equipe
//! \author pgutierrez
//! @param fenetre_affichage fenetre dans laquelle l'objet s'affichera
//! \date 25/01/17
//! \version 0.1
//!
//! Affiche tous les éléments de l'écran equipe
//!


void EcranEquipe::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage)
{

    // Seule ligne de base : SDL_FillRect(fenetre_affichage, &fenetre_affichage->clip_rect, SDL_MapRGB(fenetre_affichage->format, 0, 0, 0));


    SDL_FillRect(fenetre_affichage, &m_ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));

    //    m_nomFenetre.afficher(fenetre_affichage);

    m_tableau_equipe->afficher(fenetre_affichage);
    //A SUPPRIMER
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

void EcranEquipe::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) {
    SDL_Event evenements;

    while(SDL_PollEvent(&evenements)) {
        switch(evenements.type){
        case SDL_QUIT:
            quitter_jeu = true;
            SDL_Quit();
            break;

        case SDL_MOUSEBUTTONUP:
            if(evenements.button.button == SDL_BUTTON_LEFT) {
                clique_souris = true;
                coord_souris.first = evenements.button.x;
                coord_souris.second = evenements.button.y;
                m_tableau_equipe->gestionEvenementClique(coord_souris);
            }
            break;
        case SDL_MOUSEMOTION:
            m_tableau_equipe->gestionAffichageLigneSurvole(coord_souris);

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

EcranEquipe::~EcranEquipe() {
    if (m_tableau_equipe != nullptr){
        delete m_tableau_equipe;
    }
}



void EcranEquipe::obtenirChangement(Observable &obj){
    m_tableau_equipe->vider();
    for(Personnage * p : m_controleur->obtenirModele()->obtenirJoueur()->obtenirEquipe()->obtenirListePersonnage()){
        m_tableau_equipe->ajouterLigne(dynamic_cast<Humain *>(p));
    }
}
