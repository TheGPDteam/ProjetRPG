#include "ecranjeuprincipal.h"
#include "joueur.h"
#include "tuile.h"
#include "constantesbouton.h"
#include "utility"
#include <string>
#include <iostream>


const std::pair<int, int> coordB(890-(WIDTH_BOUTON_NORMAL/2), 200-(HEIGHT_BOUTON_NORMAL/2));
const std::pair<int, int> coordB2(890-(WIDTH_BOUTON_NORMAL/2), 250-(HEIGHT_BOUTON_NORMAL/2)); // Pk pas utiliser coord bouton avant
const std::pair<int, int> coordB3(890-(WIDTH_BOUTON_NORMAL/2), 450); // Pk pas utiliser coord bouton avant
const std::pair<int, int> coordB4(890-(WIDTH_BOUTON_NORMAL/2), 510); // Pk pas utiliser coord bouton avant
const std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

//!
//! \brief Constructeur écran jeu principal
//! \author pgutierrez
//! \date 23/11/16
//! \version 1.0
//!

EcranJeuPrincipal::EcranJeuPrincipal(Controleur* controleur)
    : EcranGeneral{controleur},
      m_objectif{(std::string)"Objectif :", SDL_Color{255,255,255,255}, (std::string)POLICE_COLLEGED, 18, std::make_pair(770,60)},
      m_nomJoueur{controleur->obtenirModele()->obtenirJoueur()->obtenirNom(), SDL_Color{255,255,255,255}, (std::string)POLICE_COLLEGED, 18, std::make_pair(770,25)},
      m_tempsRestant{"Temps restant: ", SDL_Color{255,255,255,255}, (std::string)POLICE_COLLEGED, 18, std::make_pair(770,620)}
{

    //* AJOUT DES BOUTONS *//

    SDL_Rect rect = {coordB.first, coordB.second, tailleB.first, tailleB.second};
    ajoutBoutonDansMapDeBoutons(new Bouton("Equipe", rect, m_controleur, nullptr,
                                           true, /*std::make_pair<float, float>(coordB.first+20,coordB.second+15),*/ POLICE_COLLEGED), &ActionsBoutons::boutonEquipe);

    const SDL_Rect rect2 = {coordB2.first, coordB2.second, tailleB.first, tailleB.second};
    ajoutBoutonDansMapDeBoutons(new Bouton("Inventaire", rect2, m_controleur, nullptr,
                                           true, /*std::make_pair<float, float>(coordB2.first+20,coordB2.second+15),*/ POLICE_COLLEGED), &ActionsBoutons::boutonInventaire);

    SDL_Rect rect3 = {coordB3.first, coordB3.second, tailleB.first, tailleB.second};
    ajoutBoutonDansMapDeBoutons(new Bouton("Campement", rect3, m_controleur, nullptr,
                                           true, /*std::make_pair<float, float>(coordB3.first+20,coordB3.second+15),*/ POLICE_COLLEGED), &ActionsBoutons::boutonCampement);

    SDL_Rect rect4 = {coordB4.first, coordB4.second, tailleB.first, tailleB.second};
    ajoutBoutonDansMapDeBoutons(new Bouton("Fin journee", rect4, m_controleur, nullptr,
                                           true, /* std::make_pair<float, float>(coordB4.first+20,coordB4.second+15),*/ POLICE_COLLEGED), &ActionsBoutons::boutonFinirQuete);

}


//!
//! \brief Affiche l'écran de jeu principal
//! \author pgutierrez, mleothaud
//! @param fenetre_affichage fenetre où s'affichera l'objet
//! \date 23/11/16
//! \version 1.0
//!
//! Affiche le contenu d'un écran de jeu principal
//!
void EcranJeuPrincipal::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage){
    SDL_FillRect(fenetre_affichage, &fenetre_affichage->clip_rect, SDL_MapRGB(fenetre_affichage->format, 0, 0, 0));

    m_afficheurZone.afficher(fenetre_affichage);

    Modele * m = m_controleur->obtenirModele();
    Quete * q = m->obtenirJoueur()->obtenirQuete();
    if (q->obtenirValeurAvancement() < q->obtenirValeurObjectif())
        m_objectif.mettreAJourTexte("Objectif: "+std::to_string(q->obtenirValeurAvancement())+" sur "+std::to_string(q->obtenirValeurObjectif()));
    else
        m_objectif.mettreAJourTexte("Objectif atteint");

    m_nomJoueur.mettreAJourTexte(m->obtenirJoueur()->obtenirNom());
    m_tempsRestant.mettreAJourTexte(m->obtenirTemps()->obtenirTempsAffichable(m->obtenirTemps()->obtenirTemps()));
    m_nomJoueur.afficher(fenetre_affichage);
    m_objectif.afficher(fenetre_affichage);
    m_tempsRestant.afficher(fenetre_affichage);


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
//! \date 30/11/16
//! \version 0.1
//!
//! Gère les évènements de cet écran
//!
void EcranJeuPrincipal::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris){
    SDL_Event evenements;
    Uint8 *etatTouches = SDL_GetKeyState( nullptr );
    Direction direction_deplacement = Direction::Aucune;

    // Si les touches pour aller en haut sont pressées
    if (etatTouches[ SDLK_UP ] ||  etatTouches[ SDLK_z ])
        direction_deplacement = Direction::Nord;

    // Si les touches pour aller en bas sont pressées
    if (etatTouches[ SDLK_DOWN ] ||  etatTouches[ SDLK_s ] )
        direction_deplacement = Direction::Sud;

    // Si les touches pour aller à gauche sont pressées
    if (etatTouches[ SDLK_LEFT ] ||  etatTouches[ SDLK_q ] )
        direction_deplacement = Direction::Ouest;

    // Si les touches pour aller à droite sont pressées
    if (etatTouches[ SDLK_RIGHT ] ||  etatTouches[ SDLK_d ] )
        direction_deplacement = Direction::Est;


    if (etatTouches[SDLK_ESCAPE]){
        quitter_jeu = true;
    }

    m_afficheurZone.obtenirSpritePersonnage()->deplacementJoueur(direction_deplacement);
    controleur->deplacementJoueur(direction_deplacement);

    while(SDL_PollEvent(&evenements)){
        switch(evenements.type){
            case SDL_QUIT :
                quitter_jeu = true;
                //SDL_Quit();
                break;

            case SDL_MOUSEBUTTONUP:
                if (evenements.button.button == SDL_BUTTON_LEFT){
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


EcranJeuPrincipal::~EcranJeuPrincipal(){}


void EcranJeuPrincipal::obtenirChangement(Observable& obj){
    m_afficheurZone.mettreAJour(m_carte, m_controleur->obtenirModele()->obtenirJoueur(), (dynamic_cast<Joueur*>(&obj) != nullptr) );
}


void EcranJeuPrincipal::definirCarte(Carte* carte){
    m_carte = carte;
}
