#include "ecranjeuprincipal.h"
#include "modele/joueur.h"
#include "modele/environnement/carte/tuile.h"
#include "../../interfaceutilisateur/conteneur/bouton/constantesbouton.h"
#include "utility"
#include <string>
#include <iostream>


const std::pair<int, int> coordB(890-(WIDTH_BOUTON_NORMAL/2), 200-(HEIGHT_BOUTON_NORMAL/2));
const std::pair<int, int> coordB2(890-(WIDTH_BOUTON_NORMAL/2), 250-(HEIGHT_BOUTON_NORMAL/2)); // Pk pas utiliser coord bouton avant
const std::pair<int, int> coordB3(890-(WIDTH_BOUTON_NORMAL/2), 530); // Pk pas utiliser coord bouton avant
const std::pair<int, int> coordB4(890-(WIDTH_BOUTON_NORMAL/2), 590); // Pk pas utiliser coord bouton avant
const std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

//!
//! \brief Constructeur écran jeu principal
//! \author pgutierrez
//! \date 23/11/16
//! \version 1.0
//!

EcranJeuPrincipal::EcranJeuPrincipal(Controleur* controleur)
    : EcranGeneral{controleur},
      m_spriteJoueur{new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256,256,64,64}}},
      m_objectif{(std::string)"Objectif :", SDL_Color{255,255,255,255}, (std::string)POLICE_COLLEGED, 18, std::make_pair(770,60)},
      m_nomJoueur{controleur->obtenirModele()->obtenirJoueur()->obtenirNom(), SDL_Color{255,255,255,255}, (std::string)POLICE_COLLEGED, 18, std::make_pair(770,25)},
      m_tempsRestant{"Temps restant: ", SDL_Color{255,255,255,255}, (std::string)POLICE_COLLEGED, 18, std::make_pair(770,620)}
{
    //* AJOUT DES BOUTONS *//

    SDL_Rect positionFeuilleSprite = initialiserRectangle(COORD_X_BOUTON_NORMAL, COORD_Y_BOUTON_NORMAL, WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);
    SDL_Rect positionFenetreEquipe = initialiserRectangle((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2),
                                                          (HEIGHT_FENETRE_PRINCIPALE/2)-(HEIGHT_BOUTON_NORMAL/2)+ 100,
                                                          WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    Sprite * bouton = new Sprite(SPRITES_PRINCIPAUX, positionFenetreEquipe, positionFeuilleSprite);
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2)  , (HEIGHT_FENETRE_PRINCIPALE/2)-(HEIGHT_BOUTON_NORMAL/2)+ 100 );
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);
    SDL_Rect rect= {coordB.first, coordB.second, tailleB.first, tailleB.second};
    ajoutBoutonDansMapDeBoutons(new Bouton("Equipe", rect, bouton, m_controleur, nullptr,
                                           true, std::make_pair<float, float>(coordB.first+20,coordB.second+15), POLICE_COLLEGED), &ActionsBoutons::boutonEquipe);

    /*A SUPRIMER
    ajoutBoutonDansMapDeBoutons(new Bouton{Normal, true, "Equipe", POLICE_COLLEGED, 20, coordB, tailleB, std::make_pair(coordB.first+70,coordB.second+15)}, &ActionsBoutons::boutonEquipe);
    ajoutBoutonDansMapDeBoutons(new Bouton{Normal, true, "Inventaire", POLICE_COLLEGED, 20, coordB2, tailleB, std::make_pair(coordB2.first+40,coordB2.second+15)},&ActionsBoutons::boutonInventaire);
    ajoutBoutonDansMapDeBoutons(new Bouton{Normal, true, "Aller au campement", POLICE_COLLEGED, 16, coordB3, tailleB, std::make_pair(coordB3.first+5,coordB3.second+15)},&ActionsBoutons::boutonCampement);;
    ajoutBoutonDansMapDeBoutons(new Bouton{Normal, true, "Finir journee", POLICE_COLLEGED, 19, coordB4, tailleB, std::make_pair(coordB4.first+30,coordB4.second+15)},&ActionsBoutons::boutonFinirQuete);;
    */
    //* INITIALISATION DE L'AFFICHAGE DE LA CARTE *//
    for(int i = 0; i < 12;i++)
        for(int j = 0;j< 12;j++)
            m_spritesCarte[i][j]=new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{static_cast<Sint16>(i*64),static_cast<Sint16>(j*64),0,0}, SDL_Rect{832,0,64,64}};
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

void EcranJeuPrincipal::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage)
{
    SDL_FillRect(fenetre_affichage, &fenetre_affichage->clip_rect, SDL_MapRGB(fenetre_affichage->format, 0, 0, 0));


    for(auto c : m_spritesCarte)
        for(auto x : c)
            x->afficherSprite(fenetre_affichage);

    //Sprite valise = Sprite{SPRITES_PRINCIPAUX, SDL_Rect{0,0,127,63}, SDL_Rect{256,192,63,63}};

    for(auto p : m_spriteObjets){
        Sprite valise = Sprite{SPRITES_PRINCIPAUX, SDL_Rect{(short int)(p.first*63),(short int)(p.second*63),127,63}, SDL_Rect{256,192,63,63}};
        valise.afficherSprite(fenetre_affichage);
    }

    if (m_controleur->obtenirModele()->obtenirJoueur()->obtenirQuete()->obtenirValeurAvancement() < m_controleur->obtenirModele()->obtenirJoueur()->obtenirQuete()->obtenirValeurObjectif()) {
        m_objectif.mettreAJourTexte("Objectif: "+std::to_string(m_controleur->obtenirModele()->obtenirJoueur()->obtenirQuete()->obtenirValeurAvancement())+" sur "+std::to_string(m_controleur->obtenirModele()->obtenirJoueur()->obtenirQuete()->obtenirValeurObjectif()));
    }
    else
    {
        m_objectif.mettreAJourTexte("Objectif atteint");
    }
    m_nomJoueur.mettreAJourTexte(m_controleur->obtenirModele()->obtenirJoueur()->obtenirNom());
    m_tempsRestant.mettreAJourTexte("Fin quete: "+std::to_string(m_controleur->obtenirModele()->obtenirTemps()->obtenirTempsRestant()/60)+"min"+std::to_string(m_controleur->obtenirModele()->obtenirTemps()->obtenirTempsRestant()%60));
    m_spriteJoueur->afficherSprite(fenetre_affichage);
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

void EcranJeuPrincipal::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris)
{
    SDL_Event evenements;
    Uint8 *keystates = SDL_GetKeyState( nullptr );

    //If up is pressed
    if( keystates[ SDLK_UP ] )
        controleur->deplacementJoueur(Nord);

    //If down is pressed
    if( keystates[ SDLK_DOWN ] )
        controleur->deplacementJoueur(Sud);

    //If left is pressed
    if( keystates[ SDLK_LEFT ] )
        controleur->deplacementJoueur(Ouest);

    //If right is pressed
    if( keystates[ SDLK_RIGHT ] )
        controleur->deplacementJoueur(Est);


    while(SDL_PollEvent(&evenements))
    {
        switch(evenements.type)
        {
        case SDL_QUIT:
            quitter_jeu = true;
            //SDL_Quit();
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



EcranJeuPrincipal::~EcranJeuPrincipal()
{
    delete m_spriteJoueur;
    for(int i = 0; i < 10;i++)
        for(int j = 0;j < 10;j++)
            delete m_spritesCarte[i][j];
}


void EcranJeuPrincipal::obtenirChangement(Observable& obj){

    // Test si c'est un joueur
    Joueur* joueur = dynamic_cast<Joueur*>(&obj);
    m_spriteObjets.clear();

    if(joueur!=nullptr){

        //recupère la position du joueur sur la carte
        int posX = joueur->obtenirPosition().first-5;
        int posY = joueur->obtenirPosition().second-5;

        const Zone * carte = m_carte->obtenirZoneActive();
        //on deplace la carte autour du joueur pour qu'il reste au milieu
        for(int i=posX-DECALAGE_CARTE_X_INFERIEUR;i<posX+DECALAGE_CARTE_X_SUPERIEUR;i++)
        {
            for(int j= posY-DECALAGE_CARTE_Y_INFERIEUR;j<posY+DECALAGE_CARTE_Y_SUPERIEUR;j++)
            {
                //Affichage d'arbre en dehors de la bordure de la carte
                if(i<0 || i>63 || j<0 || j>63)
                {
                    (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{256,64,64,64});
                }
                if (i < 0)
                {
                    if (j > 0 && j < 63) {
                        if (carte->obtenirTuile(0,j)->obtenirDirection()!= Direction::Aucune
                                || carte->obtenirTuile(0,j+1)->obtenirDirection()!= Direction::Aucune
                                || carte->obtenirTuile(0,j-1)->obtenirDirection()!= Direction::Aucune) //Si je suis en face d'un changement à 1 près je mets une route
                        {
                            //AFFICHER ROUTE
                            Tuile * t = carte->obtenirTuile(0,j);
                            SDL_Rect lecture = TUILE2RECT.at(t->obtenirType()).at(t->obtenirHachageJonction());
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                        } else {
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{256,64,64,64});
                        }
                    }

                } else if (i > 63)
                {
                    if (j > 0 && j < 63)
                    {
                        if (carte->obtenirTuile(63,j)->obtenirDirection()!= Direction::Aucune
                                || carte->obtenirTuile(63,j+1)->obtenirDirection()!= Direction::Aucune
                                || carte->obtenirTuile(63,j-1)->obtenirDirection()!= Direction::Aucune) //Si je suis en face d'un changement à 1 près je mets une route
                        {
                            //AFFICHER ROUTE
                            Tuile * t = carte->obtenirTuile(63,j);
                            SDL_Rect lecture = TUILE2RECT.at(t->obtenirType()).at(t->obtenirHachageJonction());
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                        } else {
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{256,64,64,64});
                        }
                    }
                } else if (j < 0)
                {
                    if (i > 0 && i < 63)
                    {
                        if (carte->obtenirTuile(i,0)->obtenirDirection()!= Direction::Aucune
                                || carte->obtenirTuile(i+1,0)->obtenirDirection()!= Direction::Aucune
                                || carte->obtenirTuile(i-1,0)->obtenirDirection()!= Direction::Aucune) //Si je suis en face d'un changement à 1 près je mets une route
                        {
                            Tuile * t = carte->obtenirTuile(i,0);
                            SDL_Rect lecture = TUILE2RECT.at(t->obtenirType()).at(t->obtenirHachageJonction());
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                        } else {
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{256,64,64,64});
                        }
                    }
                } else if (j > 63) {
                    if (i > 0 && i < 63)
                    {
                        if (carte->obtenirTuile(i,63)->obtenirDirection()!= Direction::Aucune
                                || carte->obtenirTuile(i+1,63)->obtenirDirection()!= Direction::Aucune
                                || carte->obtenirTuile(i-1,63)->obtenirDirection()!= Direction::Aucune) //Si je suis en face d'un changement à 1 près je mets une route
                        {
                            Tuile * t = carte->obtenirTuile(i,63);
                            SDL_Rect lecture = TUILE2RECT.at(t->obtenirType()).at(t->obtenirHachageJonction());
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                        } else {
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{256,64,64,64});
                        }
                    }
                }
                else
                {
                    //on recupère le type de la tuile pour l'afficher
                    std::pair<int, int> temp(i,j);
                    Tuile * t = carte->obtenirTuile(i,j);
                    if (t->obtenirDirection() == Direction::Aucune)
                    {
                        SDL_Rect lecture = TUILE2RECT.at(t->obtenirType()).at(t->obtenirHachageJonction());
                        (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                    } else
                    {
                        if (i == 0) { //Je suis a gauche donc sprite fleche de gauche
                            SDL_Rect lecture {64 , 64*3, 64, 64};
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                        } else if (i == 63) { // Je suis a droite
                            SDL_Rect lecture {0 , 64*3, 64, 64};
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                        } else if (j == 0) { // Je suis en haut
                            SDL_Rect lecture {128 , 64*3, 64, 64};
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                        } else { // Je suis en bas
                            SDL_Rect lecture {192 , 64*3, 64, 64};
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                        }
                    }

                    if(carte->objetPresent(temp))
                        m_spriteObjets.insert(std::make_pair(i-posX-DECALAGE_CARTE_X_INFERIEUR,j-posY-DECALAGE_CARTE_Y_INFERIEUR));

                }
            }
        }
    }

}

void EcranJeuPrincipal::definirCarte(Carte* carte){
    m_carte=carte;
}
