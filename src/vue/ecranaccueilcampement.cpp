#include "ecranaccueilcampement.h"
#include "bouton.h"
#include "constantesbouton.h"
#include <utility>

EcranAccueilCampement::EcranAccueilCampement(Controleur* controleur)
    :EcranGeneral{controleur},
      m_nomFenetre("Campement", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,
                   std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 50)),
      m_nombreObjets(TEXTE_NOMBRE_OBJETS+std::to_string(m_controleur->obtenirModele()->obtenirCampement()->obtenirVivres().size()+m_controleur->obtenirModele()->obtenirCampement()->obtenirObjets().size()),
                     SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,
                     std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 100)),
      m_consommation(TEXTE_CONSOMMATION+std::to_string(m_controleur->obtenirModele()->obtenirCampement()->obtenirConsommation()),
                     SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,
                     std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 150)),
      m_consoDispo(TEXTE_CONSOMMATION_DISPONIBLE+std::to_string(m_controleur->obtenirModele()->obtenirCampement()->obtenirValeurNutritiveDisponible()),
                   SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,
                   std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 200))

{
    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Retour jeu", POLICE_COLLEGED, 17, std::make_pair(WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE - 100), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL), std::make_pair(WIDTH_FENETRE_PRINCIPALE - 240, HEIGHT_FENETRE_PRINCIPALE - 82)), &ActionsBoutons::boutonJeuPrincipalCampement);
    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Deposer inventaire", POLICE_COLLEGED, 15, std::make_pair(WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE - 200), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL), std::make_pair(WIDTH_FENETRE_PRINCIPALE - 275, HEIGHT_FENETRE_PRINCIPALE - 182)), &ActionsBoutons::boutonViderInventaireCampement);
    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Liste objets", POLICE_COLLEGED, 15, std::make_pair(WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE - 300), std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL), std::make_pair(WIDTH_FENETRE_PRINCIPALE - 235, HEIGHT_FENETRE_PRINCIPALE - 282)), &ActionsBoutons::boutonListeObjet);
}

void EcranAccueilCampement::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage)
{
    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
    SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));

    m_nomFenetre.afficherTexte(fenetre_affichage);
    m_nombreObjets.afficherTexte(fenetre_affichage);
    m_consommation.afficherTexte(fenetre_affichage);
    m_consoDispo.afficherTexte(fenetre_affichage);

    afficherBoutons(coord_souris, fenetre_affichage);
}

void EcranAccueilCampement::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris)
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

EcranAccueilCampement::~EcranAccueilCampement()
{
}

void EcranAccueilCampement::obtenirChangement(Observable &obj)
{
    m_consoDispo.mettreAJourTexte(TEXTE_CONSOMMATION_DISPONIBLE+std::to_string(m_controleur->obtenirModele()->obtenirCampement()->obtenirValeurNutritiveDisponible()));
    m_consommation.mettreAJourTexte(TEXTE_CONSOMMATION+std::to_string(m_controleur->obtenirModele()->obtenirCampement()->obtenirConsommation()));
    m_nombreObjets.mettreAJourTexte(TEXTE_NOMBRE_OBJETS+std::to_string(m_controleur->obtenirModele()->obtenirCampement()->obtenirVivres().size()+m_controleur->obtenirModele()->obtenirCampement()->obtenirObjets().size()));
}
