#include "ecranchoixpersonnage.h"
#include "utility"

#include "bouton.h"
#include "constantesbouton.h"

EcranChoixPersonnage::EcranChoixPersonnage(Controleur* controleur):
    EcranGeneral{controleur},
    m_nomFenetre("Arrivee d'un survivant", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 60))
{
    int cood_x_rectangleFichePersonnage = 20;
    int cood_y_rectangleFichePersonnage = 50;

    m_rectangleFichePersonnage = {cood_x_rectangleFichePersonnage, cood_y_rectangleFichePersonnage, WIDTH_FENETRE_PRINCIPALE - cood_x_rectangleFichePersonnage * 2, HEIGHT_FENETRE_PRINCIPALE - 250};
    m_rectangleBas = {cood_x_rectangleFichePersonnage, 10 + (50 + HEIGHT_FENETRE_PRINCIPALE - 250), WIDTH_FENETRE_PRINCIPALE - cood_x_rectangleFichePersonnage * 2, (HEIGHT_FENETRE_PRINCIPALE - (HEIGHT_FENETRE_PRINCIPALE - 250)) - 80};


    Humain* h = m_controleur->journeeSuivante();

    m_zoneImagePersonnage = new TexteSDL("La Photo**", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 70));
    m_zoneNomPersonnage = new TexteSDL("Le Nom**", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 230));
    m_zoneNiveauPersonnage = new TexteSDL("Le Niveau**", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 300, m_rectangleFichePersonnage.y + 70));
    m_zoneDescriptionPersonnage = new TexteSDL("La Description**", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 600, m_rectangleFichePersonnage.y + 70));
    m_zoneStatistiquesPersonnage = new TexteSDL("Les Statistiques**",
                                                SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 600, m_rectangleFichePersonnage.y + 230));
    m_zoneQuestion = new TexteSDL("Voulez vous accepter ce survivant ?", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 400, m_rectangleFichePersonnage.y + 350));

    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Oui", POLICE_COLLEGED, 20, std::make_pair(WIDTH_FENETRE_PRINCIPALE - 290, m_rectangleBas.y + 10), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL),std::make_pair(WIDTH_FENETRE_PRINCIPALE - 280, m_rectangleBas.y + 20)), &ActionsBoutons::boutonQuete);  // PRENDRE EN COMPTE LE CHOIX
    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Non", POLICE_COLLEGED, 20, std::make_pair(WIDTH_FENETRE_PRINCIPALE - 290, m_rectangleBas.y + 60), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL),std::make_pair(WIDTH_FENETRE_PRINCIPALE - 280, m_rectangleBas.y + 20)), &ActionsBoutons::boutonQuete);
}

void EcranChoixPersonnage::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage){

    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
    SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));

    SDL_FillRect(fenetre_affichage, &m_rectangleFichePersonnage, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));
    SDL_FillRect(fenetre_affichage, &m_rectangleBas, SDL_MapRGB(fenetre_affichage->format, 100, 100, 100));

    m_nomFenetre.afficherTexte(fenetre_affichage);
    m_zoneNomPersonnage->afficherTexte(fenetre_affichage);
    m_zoneImagePersonnage->afficherTexte(fenetre_affichage);
    m_zoneNiveauPersonnage->afficherTexte(fenetre_affichage);
    m_zoneDescriptionPersonnage->afficherTexte(fenetre_affichage);
    m_zoneStatistiquesPersonnage->afficherTexte(fenetre_affichage);
    m_zoneQuestion->afficherTexte(fenetre_affichage);


    afficherBoutons(coord_souris, fenetre_affichage);


}

void EcranChoixPersonnage::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris){

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

void EcranChoixPersonnage::obtenirChangement(Observable &obj) {

}


EcranChoixPersonnage::~EcranChoixPersonnage(){

    if(m_zoneNomPersonnage != nullptr)
        delete m_zoneNomPersonnage;

    if(m_zoneDescriptionPersonnage != nullptr)
        delete m_zoneDescriptionPersonnage;
    if(m_zoneNomPersonnage != nullptr)
        delete m_zoneNomPersonnage;
    if(m_zoneImagePersonnage != nullptr)
        delete m_zoneImagePersonnage;
    if(m_zoneDescriptionPersonnage != nullptr)
        delete m_zoneDescriptionPersonnage;



}
