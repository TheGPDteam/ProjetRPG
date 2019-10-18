#include "ecranquetejoueur.h"
#include "../../interfaceutilisateur/conteneur/bouton/constantesbouton.h"
#include "../../interfaceutilisateur/conteneur/bouton/bouton.h"
#include <utility>

EcranQueteJoueur::EcranQueteJoueur(Controleur* controleur) :
    EcranGeneral{controleur},
    //m_methodeVerificationCliqueSourisSurBouton(&DictionnaireDeBoutons::verificationCliqueSourisSurBouton),
    m_nomFenetre("Que Voulez vous faire ?", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE-HEIGHT_BOUTON_NORMAL))
{
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL)-15, (HEIGHT_FENETRE_PRINCIPALE/2));
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    SDL_Rect rect = {coordB.first, coordB.second, tailleB.first, tailleB.second};
    ajoutBoutonDansMapDeBoutons(new Bouton("Recolte", rect, m_controleur, nullptr, true, POLICE_COLLEGED), &ActionsBoutons::boutonRecolteJoueur);

    std::pair<int,int> coordB2 = {(WIDTH_FENETRE_PRINCIPALE/2)+15, (HEIGHT_FENETRE_PRINCIPALE/2)};

    SDL_Rect rect2 = {coordB2.first, coordB2.second, tailleB.first, tailleB.second};
    ajoutBoutonDansMapDeBoutons(new Bouton("Chasse", rect2, m_controleur, nullptr, false, POLICE_COLLEGED), &ActionsBoutons::boutonChasseJoueur);

    short int x = (WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL)-30;
    short int y = (HEIGHT_FENETRE_PRINCIPALE/2)-HEIGHT_BOUTON_NORMAL-15;
    Uint16 largeur_fond = WIDTH_FENETRE_PRINCIPALE-x*2;
    Uint16 hauteur_fond = HEIGHT_FENETRE_PRINCIPALE-y*2;
    m_rectangle_fond = {x,y,largeur_fond, hauteur_fond};

    x = x - 2;
    y = y - 2;
    Uint16 largeur_bordure = largeur_fond+4;
    Uint16 hauteur_bordure = hauteur_fond+4;
    m_bordure = {x,y,largeur_bordure,hauteur_bordure};
}

EcranQueteJoueur::~EcranQueteJoueur(){}

void EcranQueteJoueur::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage){
    SDL_FillRect(fenetre_affichage, &m_bordure, SDL_MapRGB(fenetre_affichage->format, 75, 75, 75));
    SDL_FillRect(fenetre_affichage, &m_rectangle_fond, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));
    m_nomFenetre.afficher(fenetre_affichage);

    //A SUPPRIMER
    afficherBoutons(coord_souris, fenetre_affichage);
}

void EcranQueteJoueur::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris){
    SDL_Event evenements;

    while (SDL_PollEvent(&evenements)){
        switch(evenements.type){
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
            if (DictionnaireDeBoutons::boutonValiderEntree("Recolte",evenements,clique_souris,coord_souris)) break;
            coord_souris.first = evenements.button.x;
            coord_souris.second = evenements.button.y;
            break;

        }
    }
}

void EcranQueteJoueur::obtenirChangement(Observable &obj){}
