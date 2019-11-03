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
      m_spriteJoueur{SpritePersonnage::obtenirSpritesJoueur()},
      m_objectif{(std::string)"Objectif :", SDL_Color{255,255,255,255}, (std::string)POLICE_COLLEGED, 18, std::make_pair(770,60)},
      m_nomJoueur{controleur->obtenirModele()->obtenirJoueur()->obtenirNom(), SDL_Color{255,255,255,255}, (std::string)POLICE_COLLEGED, 18, std::make_pair(770,25)},
      m_tempsRestant{"Temps restant: ", SDL_Color{255,255,255,255}, (std::string)POLICE_COLLEGED, 18, std::make_pair(770,620)}
{

    //* AJOUT DES BOUTONS *//



    SDL_Rect rect= {coordB.first, coordB.second, tailleB.first, tailleB.second};
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
                                           true,/* std::make_pair<float, float>(coordB4.first+20,coordB4.second+15),*/ POLICE_COLLEGED), &ActionsBoutons::boutonFinirQuete);

    //* INITIALISATION DE L'AFFICHAGE DE LA CARTE *//
    for(int i = 0; i < 12; ++i)
        for(int j = 0; j < 12; ++j)
            m_spritesCarte[i][j] = new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{static_cast<Sint16>(i*64),static_cast<Sint16>(j*64),0,0}, SDL_Rect{832,0,64,64}};
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


    for(auto c : m_spritesCarte)
        for(auto x : c)
            x->afficher(fenetre_affichage);

    for(auto spriteObjet : m_spriteObjets)
        spriteObjet->afficher(fenetre_affichage);

    Modele * m = m_controleur->obtenirModele();
    Quete * q = m->obtenirJoueur()->obtenirQuete();
    if (q->obtenirValeurAvancement() < q->obtenirValeurObjectif())
        m_objectif.mettreAJourTexte("Objectif: "+std::to_string(q->obtenirValeurAvancement())+" sur "+std::to_string(q->obtenirValeurObjectif()));
    else
        m_objectif.mettreAJourTexte("Objectif atteint");

    m_nomJoueur.mettreAJourTexte(m->obtenirJoueur()->obtenirNom());
    m_tempsRestant.mettreAJourTexte(m->obtenirTemps()->obtenirTempsAffichable(m->obtenirTemps()->obtenirTemps()));
    m_spriteJoueur->afficher(fenetre_affichage);
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
    Uint8 *keystates = SDL_GetKeyState( nullptr );
    Direction direction_deplacement = Direction::Aucune;

    //If up is pressed
    if( keystates[ SDLK_UP ] ||  keystates[ SDLK_z ])
        direction_deplacement = Direction::Nord;

    //If down is pressed
    if( keystates[ SDLK_DOWN ] ||  keystates[ SDLK_s ] )
        direction_deplacement = Direction::Sud;

    //If left is pressed
    if( keystates[ SDLK_LEFT ] ||  keystates[ SDLK_q ] )
        direction_deplacement = Direction::Ouest;

    //If right is pressed
    if( keystates[ SDLK_RIGHT ] ||  keystates[ SDLK_d ] )
        direction_deplacement = Direction::Est;

    m_spriteJoueur->deplacementJoueur(direction_deplacement);
    controleur->deplacementJoueur(direction_deplacement);

    while(SDL_PollEvent(&evenements)){
        switch(evenements.type){
        case SDL_QUIT:
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



EcranJeuPrincipal::~EcranJeuPrincipal(){
    delete m_spriteJoueur;
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j)
            delete m_spritesCarte[i][j];
}

void EcranJeuPrincipal::obtenirChangement(Observable& obj){
    m_spriteObjets.clear();
    Joueur * joueur = m_controleur->obtenirModele()->obtenirJoueur();
    //recupère la position du joueur sur la zone
    int posX = joueur->obtenirPosition().first-5;
    int posY = joueur->obtenirPosition().second-5;
    const Zone * zone = m_carte->obtenirZoneActive();

    std::cout << m_carte->obtenirZoneActive()->obtenirNom() << std::endl;
    // Test si c'est un joueur
    if (dynamic_cast<Joueur*>(&obj) != nullptr){
        // on deplace la zone autour du joueur pour qu'il reste au milieu
        for (int i = posX-DECALAGE_CARTE_X_INFERIEUR; i < posX + DECALAGE_CARTE_X_SUPERIEUR; ++i){
            for (int j = posY-DECALAGE_CARTE_Y_INFERIEUR; j < posY + DECALAGE_CARTE_Y_SUPERIEUR; ++j){
                // Ne pas rendre des tuiles ou des objets en dehors de la map
                if (i > 0 && i < zone->obtenirTaille() && j > 0 && j < zone->obtenirTaille()){
                    //on recupère le type de la tuile pour l'afficher
                    std::pair<int, int> temp(i,j);
                    Tuile * t = zone->obtenirTuile(i,j);
                    // On cherche la bonne tuile sur l'atlas a partir de son numéro
                    SDL_Rect lecture = SDL_Rect{(t->obtenirNumero() % 16) * 64, (t->obtenirNumero() / 16) * 64, 64, 64};

                    (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);

                    // Affichage de la valise
                    if (zone->objetPresent(temp) && joueur->obtenirQuete()->obtenirType() == TypeQuete::QUETERECOLTE){
                        int x = i-posX-DECALAGE_CARTE_X_INFERIEUR;
                        int y = j-posY-DECALAGE_CARTE_Y_INFERIEUR;
                        m_spriteObjets.insert(new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{(short int)(x*64),(short int)(y*64),128 , 64}, SDL_Rect{4 * 64, 13 * 64, 64, 64}});
                    }
                }
            }
        }
    } else {
        for (int i = posX - DECALAGE_CARTE_X_INFERIEUR; i < posX + DECALAGE_CARTE_X_SUPERIEUR; ++i) {
            for (int j = posY - DECALAGE_CARTE_Y_INFERIEUR; j < posY + DECALAGE_CARTE_Y_SUPERIEUR; ++j) {
                if (j >= 0 && j <= 63 &&  i >= 0 && i <= 63) {
                    std::pair<int, int> temp(i,j);
                    if (zone->objetPresent(temp) && joueur->obtenirQuete()->obtenirType() == TypeQuete::QUETERECOLTE){
                        int x = i-posX-DECALAGE_CARTE_X_INFERIEUR;
                        int y = j-posY-DECALAGE_CARTE_Y_INFERIEUR;
                        m_spriteObjets.insert(new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{(short int)(x*64), (short int)(y*64), 127, 64}, SDL_Rect{4 * 64, 13 * 64, 64, 64}});
                    }
                }
            }
        }
    }
}


void EcranJeuPrincipal::definirCarte(Carte* carte){
    m_carte = carte;
}
