#include "ecranjeuprincipal.h"
#include "modele/joueur.h"
#include "modele/tuile.h"
#include "constantesbouton.h"
#include "utility"
#include <string>
#include <iostream>

std::pair<int, int> const coordB(890-(WIDTH_BOUTON_NORMAL/2), 200-(HEIGHT_BOUTON_NORMAL/2));

std::pair<int, int> const coordB2(890-(WIDTH_BOUTON_NORMAL/2), 250-(HEIGHT_BOUTON_NORMAL/2));
std::pair<int, int> const tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

//!
//! \brief Constructeur écran jeu principal
//! \author pgutierrez
//! \date 23/11/16
//! \version 1.0
//!

EcranJeuPrincipal::EcranJeuPrincipal()
    : m_spriteJoueur{new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256,0,63,63}}},
      m_texteObjectif{(std::string)"position :", SDL_Color{255,255,255,255}, (std::string)POLICE_COLLEGED, 18, std::make_pair(770,120)}
{

    //* AJOUT DES BOUTONS *//
    ajoutBoutonDansMapDeBoutons(new Bouton{Normal, true, "Equipe", POLICE_COLLEGED, 20, coordB, tailleB}, &ActionsBoutons::boutonEquipe);
    ajoutBoutonDansMapDeBoutons(new Bouton{Normal, true, "Inventaire", POLICE_COLLEGED, 20, coordB2, tailleB},&ActionsBoutons::boutonInventaire);


    //* INITIALISATION DE L'AFFICHAGE DE LA CARTE *//
    for(int i = 0; i < 12;i++)
        for(int j = 0;j< 12;j++)
            m_spritesCarte[i][j]=new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{short(i*63),short(j*63),0,0}, SDL_Rect{0,128,64,64}};
}


//!
//! \brief Affiche l'écran de jeu principal
//! \author pgutierrez
//! @param fenetre_affichage fenetre où s'affichera l'objet
//! \date 23/11/16
//! \version 0.1
//!
//! Affiche le contenu d'un écran de jeu principal
//!

void EcranJeuPrincipal::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage)
{
    SDL_FillRect(fenetre_affichage, &fenetre_affichage->clip_rect, SDL_MapRGB(fenetre_affichage->format, 0, 0, 0));


    for(auto c : m_spritesCarte)
        for(auto x : c)
            x->afficherSprite(fenetre_affichage);

    m_spriteJoueur->afficherSprite(fenetre_affichage);
    m_texteObjectif.afficherTexte(fenetre_affichage);
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
                    (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{0,320,64,64});
                }
                else
                {
                    //on recupère le type de la tuile pour l'afficher
                    std::pair<int, int> temp(i,j);
                    bool find = carte->objetPresent(temp);
                    switch(carte->obtenirTuile(i,j)->obtenirType()){
                    case TypeTuile::Eau:
                        (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{0,0,64,64});
                        break;
                    case TypeTuile::Sable:
                        if(!find)
                        {
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{0,64,64,64});
                        }
                        else {
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{64,127,64,127});
                        }
                        break;
                    case TypeTuile::Herbe:
                        if(!find)
                        {
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{0,128,64,64});
                        }
                        else {
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{64,128,64,191});
                        }
                        break;
                    case TypeTuile::Beton:
                        if(!find)
                        {
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{0,192,64,64});
                        }
                        else {
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{64,127,192, 255});
                        }
                        break;
                    case TypeTuile::Terre:
                        if(!find)
                        {
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{0,256,64,64});
                        }
                        else {
                            (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{64,127,256, 319});
                        }
                        break;
                    case TypeTuile::Arbre:
                        (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(SDL_Rect{128,291,64,64});
                    default:
                        break;
                    }
                }
            }
        }
    }

}

void EcranJeuPrincipal::definirCarte(Carte* carte){
    m_carte=carte;
}
