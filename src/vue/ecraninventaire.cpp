#include "ecraninventaire.h"
#include "bouton.h"
#include "constantesbouton.h"
#include <utility>
#include <iostream>

// A déclarer autre part ?
const short COORD_X_RECTANGLE_HAUT = 20;
const short COORD_Y_RECTANGLE_HAUT = 50;


EcranInventaire::EcranInventaire(Controleur* controleur) :
    EcranGeneral{controleur},
    m_nomFenetre("Inventaire", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 60)),
     m_compteurInventaire(-1),
     m_fondEcran{},
     m_rectangleHaut {COORD_X_RECTANGLE_HAUT, COORD_Y_RECTANGLE_HAUT, static_cast<Uint16>(WIDTH_FENETRE_PRINCIPALE - COORD_X_RECTANGLE_HAUT * 2), static_cast<Uint16>(HEIGHT_FENETRE_PRINCIPALE - 250)},
     m_rectangleBas{COORD_X_RECTANGLE_HAUT, 10 + (50 + HEIGHT_FENETRE_PRINCIPALE - 250), static_cast<Uint16>(WIDTH_FENETRE_PRINCIPALE - COORD_X_RECTANGLE_HAUT * 2), static_cast<Uint16>((HEIGHT_FENETRE_PRINCIPALE - (HEIGHT_FENETRE_PRINCIPALE - 250)) - 80)},
     m_rectangleDescription{COORD_X_RECTANGLE_HAUT + 10, COORD_Y_RECTANGLE_HAUT + 10, static_cast<Uint16>(WIDTH_FENETRE_PRINCIPALE - COORD_X_RECTANGLE_HAUT * 3), 40},
     m_zoneNomObjet{new TexteSDL("Nom", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleDescription.x + 10, m_rectangleDescription.y + 10))},
     m_zoneDescriptionObjet{new TexteSDL("Description", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(WIDTH_FENETRE_PRINCIPALE / 2 - 100, m_rectangleDescription.y + 10))},
     m_quantiteInventaire{new TexteSDL("probleme affichage", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(m_rectangleBas.w - 250, m_rectangleBas.y + m_rectangleBas.h - 50))},
     m_vecteurObjetPourAffichage(10,std::vector<TexteSDL*> (2,nullptr)),
     m_idObjetSelectionne(-1)
{
    //ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Donner", POLICE_COLLEGED, 20, std::make_pair(m_rectangleBas.x + 10, m_rectangleBas.y + 10), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL)), &ActionsBoutons::);
    //ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Jeter", POLICE_COLLEGED, 20, std::make_pair(WIDTH_FENETRE_PRINCIPALE - 50, m_rectangleBas.y + 10), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL)), &ActionsBoutons::boutonJeuPrincipal);
    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Quitter", POLICE_COLLEGED, 20, std::make_pair(WIDTH_FENETRE_PRINCIPALE - 290, m_rectangleBas.y + 10), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL), std::make_pair(WIDTH_FENETRE_PRINCIPALE - 280, m_rectangleBas.y + 20)), &ActionsBoutons::boutonJeuPrincipal);
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
    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
    SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));

    SDL_FillRect(fenetre_affichage, &m_rectangleHaut, SDL_MapRGB(fenetre_affichage->format, 100, 100, 100));
    SDL_FillRect(fenetre_affichage, &m_rectangleBas, SDL_MapRGB(fenetre_affichage->format, 100, 100, 100));
    SDL_FillRect(fenetre_affichage, &m_rectangleDescription, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));

    m_nomFenetre.afficherTexte(fenetre_affichage);
    m_zoneNomObjet->afficherTexte(fenetre_affichage);
    m_zoneDescriptionObjet->afficherTexte(fenetre_affichage);
    m_quantiteInventaire->afficherTexte(fenetre_affichage);

    if(!m_vecteurObjetPourAffichage.empty())
    {
        for(unsigned int i = 0; i+1 <= m_vecteurObjetPourAffichage.size(); ++i)
        {
            for(int j = 0; j < 2; ++j)
            {
                if(m_vecteurObjetPourAffichage[i][j] != nullptr)
                    m_vecteurObjetPourAffichage[i][j]->afficherTexte(fenetre_affichage);
            }
        }
    }

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
    if(m_zoneDescriptionObjet != nullptr)
    {
        delete m_zoneDescriptionObjet;
    }

    if(m_zoneNomObjet != nullptr)
    {
        delete m_zoneNomObjet;
    }

    if(m_quantiteInventaire != nullptr)
    {
        delete m_quantiteInventaire;
    }

    if(!m_vecteurObjetPourAffichage.empty())
    {
        for(int i = 0; i < 0; ++i)
        {
            for(int j = 0; j < 2; ++j)
            {
                delete m_vecteurObjetPourAffichage[i][j];
            }
        }
    }
}



void EcranInventaire::obtenirChangement(Observable &obj)
{
    Joueur* joueur = dynamic_cast<Joueur *>(&obj);
    if (joueur == nullptr) return;

    if (m_compteurInventaire == -1)
        m_compteurInventaire = joueur->obtenirInventaireJoueur()->obtenirNombreObjet();


    if( joueur->obtenirInventaireJoueur()->obtenirNombreObjet() != m_compteurInventaire)
    {
        //m_vecteurObjetPourAffichage.resize(joueur->obtenirInventaireJoueur()->obtenirTailleMax());


        definirObjetPourAffichage(joueur->obtenirInventaireJoueur()->obtenirObjets());
        definirEtatQuantite(joueur->obtenirInventaireJoueur()->obtenirNombreObjet());
    }
}


bool EcranInventaire::definirObjetPourAffichage(std::vector<Objet *> objets)
{
    int cpt = 0;
    bool ajoutEffectue = false;

    for(Objet * objet : objets)
    {
        //if(m_vecteurObjetPourAffichage[cpt][0]->getTexteStr().compare(objet->obtenirNom()) != 0 && m_vecteurObjetPourAffichage[cpt][1]->getTexteStr().compare(objet->obtenirDescription()) != 0)
        //{

            m_vecteurObjetPourAffichage[cpt][0] = new TexteSDL(objet->obtenirNom(), SDL_Color{0,0,0,255}, POLICE_COLLEGED, 18,
                                                               std::make_pair(m_rectangleDescription.x + 10, (m_rectangleDescription.y + 50) + cpt * 25)); // Nom
            m_vecteurObjetPourAffichage[cpt][1] = new TexteSDL(objet->obtenirDescription(), SDL_Color{0,0,0,255}, POLICE_COLLEGED, 18, std::make_pair(WIDTH_FENETRE_PRINCIPALE/2 - 150, (m_rectangleDescription.y + 50) + cpt * 25)); // Description
            ajoutEffectue = true;
        //}

        cpt++;
    }

    return ajoutEffectue;
}



void EcranInventaire::definirEtatQuantite(int quantite_objets)
{
    std::string tmp = "Stockage : " + std::to_string(quantite_objets) + " - " + std::to_string(m_vecteurObjetPourAffichage.size());

    if(m_quantiteInventaire != nullptr)
    {
        m_quantiteInventaire->mettreAJourTexte(tmp);
    }
}
