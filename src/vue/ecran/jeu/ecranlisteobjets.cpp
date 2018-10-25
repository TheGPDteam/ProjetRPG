#include "ecranlisteobjets.h"

#include "../../interfaceutilisateur/conteneur/bouton/bouton.h"
#include "../../interfaceutilisateur/conteneur/bouton/constantesbouton.h"

const int ESPACE_X_RECTANGLE_OBJET = 20;
const int ESPACE_Y_RECTANGLE_OBJET = 90;
const int LARGEUR_RECTANGLE_OBJET = WIDTH_FENETRE_PRINCIPALE -  2 * ESPACE_X_RECTANGLE_OBJET;
const int HAUTEUR_RECTANGLE_OBJET = HEIGHT_FENETRE_PRINCIPALE - 2 * ESPACE_Y_RECTANGLE_OBJET;
const std::pair<int, int> coordB(WIDTH_FENETRE_PRINCIPALE-(WIDTH_BOUTON_NORMAL)-75, HEIGHT_FENETRE_PRINCIPALE-(HEIGHT_BOUTON_NORMAL*3)-25);
const std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

EcranListeObjet::EcranListeObjet(Controleur *controleur)
    :EcranGeneral{controleur},
      m_nomFenetre("Liste des objets", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 30,
                   std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 100)),
      m_nomObjet("Nom", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20,
                 std::make_pair(0,0), std::make_pair(150, 250)),
      m_descObjet("Description", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20,
                  std::make_pair(350,0), std::make_pair(150, 250))
{
    m_rectangleFicheObjet = {ESPACE_X_RECTANGLE_OBJET, ESPACE_Y_RECTANGLE_OBJET, LARGEUR_RECTANGLE_OBJET, HAUTEUR_RECTANGLE_OBJET};
    //A SUPPRIMER
    //ajoutBoutonDansMapDeBoutons(new Bouton{Normal, true, "Retour Jeu", POLICE_COLLEGED, 20, coordB, tailleB, std::make_pair(coordB.first+40,coordB.second+15)}, &ActionsBoutons::boutonJeuPrincipal);
}

void EcranListeObjet::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage)
{
    afficherFondEcran(fenetre_affichage);
    SDL_FillRect(fenetre_affichage, &m_rectangleFicheObjet, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));

    m_nomFenetre.afficher(fenetre_affichage);
    m_nomObjet.afficher(fenetre_affichage);
    m_descObjet.afficher(fenetre_affichage);

    //A SUPPRIMER
    //afficherBoutons(coord_souris, fenetre_affichage);

    int i=0;
    for(auto o : m_controleur->obtenirModele()->obtenirCampement()->obtenirObjets())
    {
        ++i;
        if (i==11)
        {
            break;
        }
        TexteSDL zoneTempNom = TexteSDL (o->obtenirNom(),SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(50, 120 + 30 * i));
        zoneTempNom.afficher(fenetre_affichage);
        TexteSDL zoneTempNiv = TexteSDL (o->obtenirDescription(),SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(350, 120 + 30 * i));
        zoneTempNiv.afficher(fenetre_affichage);
    }
}

void EcranListeObjet::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris){

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

void EcranListeObjet::obtenirChangement(Observable &obj) {

}
