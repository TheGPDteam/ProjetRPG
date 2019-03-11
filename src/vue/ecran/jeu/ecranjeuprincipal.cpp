#include "ecranjeuprincipal.h"
#include "joueur.h"
#include "tuile.h"
#include "constantesbouton.h"
#include "utility"
#include <string>
#include <iostream>
#include "vue.h"

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
      m_spriteJoueur{new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{5*63,5*63,127,63}, SDL_Rect{256,256,64,64}}},
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
    for(int i = 0; i < TAILLE_CARTE_AFFICHAGE;i++)
        for(int j = 0;j< TAILLE_CARTE_AFFICHAGE;j++)
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
    m_tempsRestant.mettreAJourTexte("Fin quete: "+std::to_string(m->obtenirTemps()->obtenirTempsRestantJournee()/60)+"min"+std::to_string(m->obtenirTemps()->obtenirTempsRestantJournee()%60));
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

void EcranJeuPrincipal::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris)
{
    SDL_Event evenements;
    Uint8 *keystates = SDL_GetKeyState( nullptr );

    //If up is pressed
    if( keystates[ SDLK_UP ] ||  keystates[ SDLK_z ])
        controleur->deplacementJoueur(Nord);

    //If down is pressed
    if( keystates[ SDLK_DOWN ] ||  keystates[ SDLK_s ] )
        controleur->deplacementJoueur(Sud);

    //If left is pressed
    if( keystates[ SDLK_LEFT ] ||  keystates[ SDLK_q ] )
        controleur->deplacementJoueur(Ouest);

    //If right is pressed
    if( keystates[ SDLK_RIGHT ] ||  keystates[ SDLK_d ] )
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
    for (auto ptr : m_spriteObjets){
        delete ptr;
    }
}

Sprite * EcranJeuPrincipal::creerSpriteTuile(int tuileX, int tuileY, int posDessinX, int posDessinY){
    Sprite * s = nullptr;
    if(tuileX < 0 || tuileX >= TAILLE_ZONE || tuileY < 0 || tuileY >= TAILLE_ZONE) // arbre
        s = new Sprite(SPRITES_PRINCIPAUX, SDL_Rect{posDessinX, posDessinY, 0,0}, SDL_Rect{256,64,64,64});
    else {
        Zone * carte = m_carte->obtenirZoneActive();
        Tuile * t = carte->obtenirTuile(tuileX, tuileY);
        SDL_Rect lecture = TUILE2RECT.at(t->obtenirType()).at(t->obtenirHachageJonction());
        s = new Sprite(SPRITES_PRINCIPAUX, SDL_Rect{posDessinX, posDessinY, 0,0}, lecture);
    }
    return s;
}


Sprite * EcranJeuPrincipal::creerSpriteObjet(Joueur * joueur, int tuileX, int tuileY, int posDessinX, int posDessinY){
    Sprite *s = nullptr;
    Zone * carte = m_carte->obtenirZoneActive();
    std::pair<int, int > temp = std::make_pair(tuileX, tuileY);

    if(carte->objetPresent(temp) && joueur->obtenirQuete()->obtenirType() == TypeQuete::QUETERECOLTE){
        s = new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{posDessinX, posDessinY,0,0}, SDL_Rect{256,192,63,63}};
    }
    return s;
}

void EcranJeuPrincipal::animerDeplacement(Joueur * joueur, SDL_Surface * ecran){
    Direction dirJoueur = joueur->obtenirDirection();
    int posC = joueur->obtenirPosition().first;
    int posL = joueur->obtenirPosition().second;
    int precedentC = posC + (dirJoueur == Est ? -1 : (dirJoueur == Ouest ? 1 :0 ));
    int precedentL = posL + (dirJoueur == Nord ? 1 : (dirJoueur == Sud ? -1 : 0));
    //    on augmente le nombre de tuile en hauteur ou largeur pour permettre l'animation dans la bonne direction
    int nombreTuileLargeur = TAILLE_CARTE_AFFICHAGE + ((dirJoueur==Direction::Est || dirJoueur ==Direction::Ouest)?1:0);
    int nombreTuileHauteur = TAILLE_CARTE_AFFICHAGE + ((nombreTuileLargeur==TAILLE_CARTE_AFFICHAGE)?1:0);

    SDL_Surface *horsEcran = SDL_CreateRGBSurface(SDL_HWSURFACE, nombreTuileLargeur*64, nombreTuileHauteur*64,BPP ,0,0,0,0);
    int decalageVueX = (dirJoueur == Est ? 0 : (dirJoueur == Ouest ? 1 : 0));
    int decalageVueY = (dirJoueur == Sud ? 0 : (dirJoueur == Nord ? 1 : 0));
    for(int i = 0; i < TAILLE_CARTE_AFFICHAGE; ++i){
        for (int j = 0; j < TAILLE_CARTE_AFFICHAGE; ++j){
            (m_spritesCarte[i][j])->bougerSprite(decalageVueX, decalageVueY);
            (m_spritesCarte[i][j])->afficher(horsEcran);
            (m_spritesCarte[i][j])->bougerSprite(-decalageVueX, -decalageVueY);
        }
    }

    std::vector<Sprite *> sprites, spriteObjets;
    if(dirJoueur == Est || dirJoueur == Ouest){
        int numeroColonneTuiles = posC + (dirJoueur == Est ? TAILLE_CARTE_AFFICHAGE/2 : - TAILLE_CARTE_AFFICHAGE/2 + 1);
        int numeroLigneTuilesDepart = posL - TAILLE_CARTE_AFFICHAGE/2 + 1;
        int numeroLigneTuilesArrivee = posL  + TAILLE_CARTE_AFFICHAGE/2;
        for(int j = numeroLigneTuilesDepart; j<=numeroLigneTuilesArrivee; ++j){
            Sprite * s = creerSpriteTuile(numeroColonneTuiles, j, (dirJoueur == Est ? (TAILLE_CARTE_AFFICHAGE)*64 : 0), (j-numeroLigneTuilesDepart)*64) ;
            sprites.push_back(s);

            s = creerSpriteObjet(joueur, numeroColonneTuiles, j, (dirJoueur == Est ? (TAILLE_CARTE_AFFICHAGE)*64 : 0), (j-numeroLigneTuilesDepart)*64);
            if( s != nullptr)
                spriteObjets.push_back(s);

        }
    }
    else {
        int numeroColonneTuilesDepart = posC - TAILLE_CARTE_AFFICHAGE/2 + 1 ;
        int numeroColonneTuilesArrivee= posC + TAILLE_CARTE_AFFICHAGE/2;
        int numeroLigneTuiles = (dirJoueur == Sud ? posL + TAILLE_CARTE_AFFICHAGE/2 : posL - TAILLE_CARTE_AFFICHAGE/2 + 1);

        for(int i = numeroColonneTuilesDepart; i<= numeroColonneTuilesArrivee; ++i){
            Sprite * s = creerSpriteTuile(i,numeroLigneTuiles, (i-numeroColonneTuilesDepart)*64, (dirJoueur == Sud ? TAILLE_CARTE_AFFICHAGE*64 : 0));
            sprites.push_back(s);

            s = creerSpriteObjet(joueur, i,numeroLigneTuiles, (i-numeroColonneTuilesDepart)*64, (dirJoueur == Sud ? TAILLE_CARTE_AFFICHAGE*64 : 0));
            if( s != nullptr)
                spriteObjets.push_back(s);

        }
    }

    for(int l = precedentL - TAILLE_CARTE_AFFICHAGE / 2 +1;l <= precedentL + TAILLE_CARTE_AFFICHAGE/2; ++l){
        for(int c = precedentC - TAILLE_CARTE_AFFICHAGE / 2 + 1; c <= precedentC +TAILLE_CARTE_AFFICHAGE / 2 ; ++c){
            Sprite *s = creerSpriteObjet(joueur, c, l , ((dirJoueur == Ouest ? 1 : 0)+c-(precedentC - TAILLE_CARTE_AFFICHAGE / 2 + 1))*64, ((dirJoueur == Nord ? 1 : 0 )+l-(precedentL - TAILLE_CARTE_AFFICHAGE / 2 +1))*64);
            if( s != nullptr) {
                spriteObjets.push_back(s);
            }
        }
    }

    for(unsigned int i = 0;  i < sprites.size(); ++i){
        sprites[i]->afficher(horsEcran);
        delete sprites[i];
    }


    for(unsigned int i = 0;  i < spriteObjets.size(); ++i){
        spriteObjets[i]->afficher(horsEcran);
        delete spriteObjets[i];
    }

    SDL_Rect rectLecture = {decalageVueX*64, decalageVueY*64 ,TAILLE_CARTE_AFFICHAGE*64, TAILLE_CARTE_AFFICHAGE*64};
    float  decalageX = 64. * (dirJoueur == Est ? 1 : (dirJoueur == Ouest ? -1 : 0));
    float decalageY = 64. * (dirJoueur == Sud ? 1 : (dirJoueur == Nord ? -1 : 0));

    SDL_Rect dest_rect = {0, 0,TAILLE_CARTE_AFFICHAGE*64, TAILLE_CARTE_AFFICHAGE*64};
    for(int i = 1; i<= NB_ETAPES_ANIMATION; ++i){
        SDL_Rect dep_courant = {rectLecture.x+decalageX*i*1./NB_ETAPES_ANIMATION, rectLecture.y+decalageY*i*1./NB_ETAPES_ANIMATION, rectLecture.w, rectLecture.h};
        SDL_BlitSurface(horsEcran, &dep_courant, ecran,&dest_rect);
        m_spriteJoueur->afficher(ecran);
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(horsEcran);

}

void EcranJeuPrincipal::obtenirChangement(Observable& obj){
    for (auto ptr : m_spriteObjets){
        delete ptr;
    }
    m_spriteObjets.clear();
    Joueur * joueur = m_controleur->obtenirModele()->obtenirJoueur();
    //recupère la position du joueur sur la carte
    int posX = joueur->obtenirPosition().first-5;
    int posY = joueur->obtenirPosition().second-5;
    const Zone * carte = m_carte->obtenirZoneActive();

    Joueur * j = dynamic_cast<Joueur*>(&obj);
    // Test si c'est un joueur
    if(j !=nullptr){
        if(m_controleur->obtenirVue()->obtenirEcranCourant() == TypeEcran::JeuPrincipal)
            animerDeplacement(joueur, m_controleur->obtenirVue()->obtenirFenetrePrincipale());

        //on deplace la carte autour du joueur pour qu'il reste au milieu
        for(int i=posX-DECALAGE_CARTE_X_INFERIEUR;i<posX+DECALAGE_CARTE_X_SUPERIEUR;i++)
        {
            for(int j= posY-DECALAGE_CARTE_Y_INFERIEUR;j<posY+DECALAGE_CARTE_Y_SUPERIEUR;j++)
            {
                //on recupère le type de la tuile pour l'afficher
                std::pair<int, int> temp(i,j);
                Tuile * t = carte->obtenirTuile(i,j);
                if (t->obtenirDirectionChangementZone() == Direction::Aucune)
                {
                    SDL_Rect lecture = TUILE2RECT.at(t->obtenirType()).at(t->obtenirHachageJonction());
                    (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                } else
                {
                    if (i == DECALAGE_TUILE) { //Je suis a gauche donc sprite fleche de gauche
                        SDL_Rect lecture {64 , 64*3, 64, 64};
                        (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                    } else if (i == TAILLE_ZONE-1-DECALAGE_TUILE) { // Je suis a droite
                        SDL_Rect lecture {0 , 64*3, 64, 64};
                        (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                    } else if (j == DECALAGE_TUILE) { // Je suis en haut
                        SDL_Rect lecture {128 , 64*3, 64, 64};
                        (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                    } else { // Je suis en bas
                        SDL_Rect lecture {192 , 64*3, 64, 64};
                        (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                    }
                }

                if(carte->objetPresent(temp) && joueur->obtenirQuete()->obtenirType() == TypeQuete::QUETERECOLTE){
                    int x = i-posX-DECALAGE_CARTE_X_INFERIEUR;
                    int y = j-posY-DECALAGE_CARTE_Y_INFERIEUR;
                    m_spriteObjets.insert(new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{(short int)(x*64),(short int)(y*64),127,64}, SDL_Rect{256,192,64,64}});
                }
            }
        }

    }else {
        for(int i=posX-DECALAGE_CARTE_X_INFERIEUR;i<posX+DECALAGE_CARTE_X_SUPERIEUR;i++)
        {
            for(int j= posY-DECALAGE_CARTE_Y_INFERIEUR;j<posY+DECALAGE_CARTE_Y_SUPERIEUR;j++)
            {
                if ( j >= 0 && j <= TAILLE_ZONE-1 &&  i >= 0 && i <= TAILLE_ZONE-1) {
                    std::pair<int, int> temp(i,j);
                    if(carte->objetPresent(temp) && joueur->obtenirQuete()->obtenirType() == TypeQuete::QUETERECOLTE){
                        int x = i-posX-DECALAGE_CARTE_X_INFERIEUR;
                        int y = j-posY-DECALAGE_CARTE_Y_INFERIEUR;
                        m_spriteObjets.insert(new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{(short int)(x*63),(short int)(y*63),127,63}, SDL_Rect{256,192,63,63}});
                    }
                }
            }
        }
    }
}


void EcranJeuPrincipal::definirCarte(Carte* carte){
    m_carte=carte;
}
