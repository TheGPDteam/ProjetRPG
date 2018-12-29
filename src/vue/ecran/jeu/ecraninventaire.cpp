#include "ecraninventaire.h"
#include "bouton/bouton.h"
#include "constantesbouton.h"
#include <utility>
#include <iostream>

// A déclarer autre part ?
const short COORD_X_RECTANGLE_HAUT = 20;
const short COORD_Y_RECTANGLE_HAUT = 50;
//SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};


EcranInventaire::EcranInventaire(Controleur* controleur) :
    EcranGeneral{controleur},
    m_nomFenetre("Inventaire", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 60)),
    m_compteurInventaire(-1),
    m_fondEcran{},
    m_rectangleHaut(initialiserRectangle(m_ecran.x, m_ecran.y, m_ecran.w, 64*8)),
    m_rectangleBas{COORD_X_RECTANGLE_HAUT, 10 + (50 + HEIGHT_FENETRE_PRINCIPALE - 250), static_cast<Uint16>(WIDTH_FENETRE_PRINCIPALE - COORD_X_RECTANGLE_HAUT * 2), static_cast<Uint16>((HEIGHT_FENETRE_PRINCIPALE - (HEIGHT_FENETRE_PRINCIPALE - 250)) - 80)},
    m_rectangleDescription{COORD_X_RECTANGLE_HAUT + 10, COORD_Y_RECTANGLE_HAUT + 10, static_cast<Uint16>(WIDTH_FENETRE_PRINCIPALE - COORD_X_RECTANGLE_HAUT * 3), 40},
    m_quantiteInventaire{new TexteSDL("probleme affichage", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(m_rectangleBas.w - 250, m_rectangleBas.y + m_rectangleBas.h - 50))},
    m_idObjetSelectionne(-1)
{
    /* A SUPPRIMER
    //ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Donner", POLICE_COLLEGED, 20, std::make_pair(m_rectangleBas.x + 10, m_rectangleBas.y + 10), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL)), &ActionsBoutons::);
    //ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Jeter", POLICE_COLLEGED, 20, std::make_pair(WIDTH_FENETRE_PRINCIPALE - 50, m_rectangleBas.y + 10), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL)), &ActionsBoutons::boutonJeuPrincipal);
    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Quitter", POLICE_COLLEGED, 18, std::make_pair(WIDTH_FENETRE_PRINCIPALE - 290, m_rectangleBas.y + 10), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL), std::make_pair(WIDTH_FENETRE_PRINCIPALE - 217, m_rectangleBas.y + 27)), &ActionsBoutons::boutonJeuPrincipal);
    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Aller au camp", POLICE_COLLEGED, 16, std::make_pair(100, m_rectangleBas.y + 10), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL), std::make_pair(100 + 40, m_rectangleBas.y + 27)), &ActionsBoutons::boutonCampement);
    */
    const std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    SDL_Rect rect = {WIDTH_FENETRE_PRINCIPALE - 290, m_rectangleBas.y + 10, tailleB.first, tailleB.second};
    SDL_Rect rect2 = {100, m_rectangleBas.y + 10, tailleB.first, tailleB.second};
    ajoutBoutonDansMapDeBoutons(new Bouton("Retour jeu", rect, m_controleur, nullptr,
                                           true, /*std::make_pair<float, float>(rect.x + 20,rect.y + 15),*/ POLICE_COLLEGED), &ActionsBoutons::boutonJeuPrincipal);
    ajoutBoutonDansMapDeBoutons(new Bouton("Aller au camp", rect2, m_controleur, nullptr,
                                           true, /*std::make_pair<float, float>(rect.x+20,rect.y+15),*/ POLICE_COLLEGED), &ActionsBoutons::boutonCampement);

    m_tableau_objets = TableauDefilable::tableauObjet(m_rectangleHaut, m_controleur, "Inventaire", true);

    obtenirChangement(*m_controleur->obtenirModele()->obtenirJoueur()->obtenirInventaire());

}



//!
//! \brief Affiche l'ecran inventaire
//! \author pgutierrez
//! @param fenetre_affichage fenetre dans laquelle l'objet s'affichera
//! \date 25/01/17
//! \version 0.1
//!
//! Affiche tout les éléments de l'écran inventaire
//!


void EcranInventaire::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage)
{
    SDL_FillRect(fenetre_affichage, &m_ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));


    m_quantiteInventaire->afficher(fenetre_affichage);


    m_tableau_objets->afficher(fenetre_affichage);
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

void EcranInventaire::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris)
{
    SDL_Event evenements;

    while(SDL_PollEvent(&evenements))
    {
        SDL_EnableKeyRepeat(10, 10);
        switch(evenements.type)
        {
        case SDL_QUIT:
            quitter_jeu = true;
            SDL_Quit();
            break;

        case SDL_MOUSEBUTTONUP:
            if(evenements.button.button == SDL_BUTTON_LEFT)
            {
                m_tableau_objets->gestionEvenementClique(coord_souris);
                clique_souris = true;
                coord_souris.first = evenements.button.x;
                coord_souris.second = evenements.button.y;
            }
            break;
                    case SDL_MOUSEMOTION:
            coord_souris.first = evenements.button.x;
            coord_souris.second = evenements.button.y;
            m_tableau_objets->gestionAffichageLigneSurvole(coord_souris);
            break;

        default:
            coord_souris.first = evenements.button.x;
            coord_souris.second = evenements.button.y;
            break;

        }
    }
}


//!
//! \brief  Destructeur de l'ecran inventaire
//! \author pgutierrez
//! \date 25/01/17
//! \version 1.0
//!
//! Détruit tout les élément de l'ecran inventaire
//!

EcranInventaire::~EcranInventaire()
{
    if(m_quantiteInventaire != nullptr)
    {
        delete m_quantiteInventaire;
    }

    if(m_tableau_objets != nullptr)
    {
        delete m_tableau_objets;
    }
}



void EcranInventaire::obtenirChangement(Observable &obj)
{
    Inventaire * inventaire = m_controleur->obtenirModele()->obtenirJoueur()->obtenirInventaire();
    definirEtatQuantite(inventaire);
    m_tableau_objets->obtenirTableauDonnees()->vider();
    for(auto o : inventaire->obtenirObjets())
    {
        m_tableau_objets->obtenirTableauDonnees()->ajouterLigne(o);
    }
}


void EcranInventaire::definirEtatQuantite(Inventaire * inventaireJ)
{
    if(inventaireJ == nullptr) return;
    std::string tmp = "Stockage : " + std::to_string(inventaireJ->obtenirNombreObjet()) + " - " + std::to_string(inventaireJ->obtenirTailleMax());

    if(m_quantiteInventaire != nullptr)
    {
        m_quantiteInventaire->mettreAJourTexte(tmp);
    }
}
