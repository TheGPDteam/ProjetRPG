#include "ecranlisteobjets.h"

#include "../../interfaceutilisateur/conteneur/bouton/bouton.h"
#include "../../interfaceutilisateur/conteneur/bouton/constantesbouton.h"
#include "tableau.h"

const std::pair<int, int> coordB(WIDTH_FENETRE_PRINCIPALE-(WIDTH_BOUTON_NORMAL)-75, HEIGHT_FENETRE_PRINCIPALE-(HEIGHT_BOUTON_NORMAL*3)-25);
const std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

EcranListeObjet::EcranListeObjet(Controleur *controleur)
    :EcranGeneral{controleur},
      m_nomFenetre("Liste des objets", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 30,
                   std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 100))
{
    m_rectangleFicheObjet = {0, 0, 0, 0};

    m_tableau_objets = TableauDefilable::tableauObjet(m_rectangleFicheObjet, controleur, "Liste des objets", true);

    SDL_Rect rect = {coordB.first, coordB.second, tailleB.first, tailleB.second};
    ajoutBoutonDansMapDeBoutons(new Bouton("Retour jeu", rect, m_controleur, nullptr,
                                           true, /*std::make_pair<float, float>(coordB.first+40,coordB.second+15),*/ POLICE_COLLEGED), &ActionsBoutons::boutonJeuPrincipal);
    obtenirChangement(*m_controleur->obtenirModele()->obtenirCampement());
}

void EcranListeObjet::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage){
    afficherFondEcran(fenetre_affichage);
    SDL_FillRect(fenetre_affichage, &m_rectangleFicheObjet, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));

    m_tableau_objets->afficher(fenetre_affichage);

    //A SUPPRIMER
    afficherBoutons(coord_souris, fenetre_affichage);
}

void EcranListeObjet::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris){

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
                m_tableau_objets->gestionEvenementClique(coord_souris);
            }
            break;
        case SDL_MOUSEMOTION :
            m_tableau_objets->gestionAffichageLigneSurvole(coord_souris);

        default:
            coord_souris.first = evenements.button.x;
            coord_souris.second = evenements.button.y;
            break;
        }
    }
}

void EcranListeObjet::obtenirChangement(Observable &obj) {
    m_tableau_objets->vider();
    for(auto o : m_controleur->obtenirModele()->obtenirCampement()->obtenirObjets()){
        m_tableau_objets->ajouterLigne(o);
    }

    for(auto o : m_controleur->obtenirModele()->obtenirCampement()->obtenirVivres()){
        m_tableau_objets->ajouterLigne(o);
    }
}
