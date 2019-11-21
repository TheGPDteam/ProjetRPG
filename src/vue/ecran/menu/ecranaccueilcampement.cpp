#include "ecranaccueilcampement.h"
#include "bouton.h"
#include "constantesbouton.h"
#include <utility>


EcranAccueilCampement::EcranAccueilCampement(Controleur* controleur, GestionnaireRessource* gestionnaireRessource)
    :EcranGeneral{controleur, gestionnaireRessource},
      m_nomFenetre("Campement", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20,
                   std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 50)),
      m_nombreObjets(TEXTE_NOMBRE_OBJETS+std::to_string(m_controleur->obtenirModele()->obtenirCampement()->obtenirVivres().size()+m_controleur->obtenirModele()->obtenirCampement()->obtenirObjets().size()),
                     SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20,
                     std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 100)),
      m_consommation(TEXTE_CONSOMMATION+std::to_string(m_controleur->obtenirModele()->obtenirCampement()->obtenirConsommation()),
                     SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20,
                     std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 150)),
      m_consoDispo(TEXTE_CONSOMMATION_DISPONIBLE+std::to_string(m_controleur->obtenirModele()->obtenirCampement()->obtenirValeurNutritiveDisponible()),
                  SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20,
                   std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 200))

{
    SDL_Rect rectTableauObjet = {0.1*WIDTH_FENETRE_PRINCIPALE, 0.3*HEIGHT_FENETRE_PRINCIPALE, 0.8*WIDTH_FENETRE_PRINCIPALE-290, 0.6*HEIGHT_FENETRE_PRINCIPALE,};
    m_tableau_objets = TableauDefilable::tableauObjet(rectTableauObjet, controleur, "Liste des objets", true);
    const std::pair<int, int> coordB(WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE - 100);
    const std::pair<int, int> coordB2(WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE - 200);
    const std::pair<int, int> coordB3(WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE - 300);
    const std::pair<int, int> coordB4(WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE - 400);
    const std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    SDL_Rect rect = {coordB.first, coordB.second, tailleB.first, tailleB.second};
    SDL_Rect rect2 = {coordB2.first, coordB2.second, tailleB.first, tailleB.second};
    SDL_Rect rect3 = {coordB3.first, coordB3.second, tailleB.first, tailleB.second};
    SDL_Rect rect4 = {coordB4.first, coordB4.second, tailleB.first, tailleB.second};
    ajoutBoutonDansMapDeBoutons(new Bouton("Retour Jeu", rect, m_controleur, nullptr,
                                           true, /*std::make_pair<float, float>(coordB.first+20,coordB.second+15),*/ POLICE_COLLEGED), &ActionsBoutons::boutonJeuPrincipal);
    ajoutBoutonDansMapDeBoutons(new Bouton("Deposer Inventaire", rect3, m_controleur, nullptr,
                                           true, /*std::make_pair<float, float>(coordB2.first+20,coordB2.second+15), */POLICE_COLLEGED), &ActionsBoutons::boutonViderInventaireCampement);
    ajoutBoutonDansMapDeBoutons(new Bouton("CONSTRUCTION DU BUS", rect4, m_controleur, nullptr,
                                           true, /*std::make_pair<float, float>(coordB3.first+20,coordB3.second+15),*/ POLICE_COLLEGED), &ActionsBoutons::boutonEtatQuetePrincipale);


    m_fond = SDL_LoadBMP("../rsc/sprites/ecran_campement.bmp");
    obtenirChangement(*m_controleur->obtenirModele()->obtenirCampement());

}

void EcranAccueilCampement::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage){
    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
    SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));
    SDL_Rect dest_rect = {0, 0, 0, 0};
    SDL_BlitSurface(m_fond,&ecran,fenetre_affichage,&dest_rect);

    m_nomFenetre.afficher(fenetre_affichage);
    m_nombreObjets.afficher(fenetre_affichage);
    m_consommation.afficher(fenetre_affichage);
    m_consoDispo.afficher(fenetre_affichage);
    m_tableau_objets->afficher(fenetre_affichage);
    Bouton * b =obtenirBouton("Deposer Inventaire");
    assert(b!= nullptr);
        bool inventaireVide = m_controleur->obtenirModele()->obtenirJoueur()->obtenirInventaire()->obtenirNombreObjet() == 0;
        if(inventaireVide)
            remiseAZeroBoutons(b);
        b->definirCliquable(!inventaireVide);

    afficherBoutons(coord_souris, fenetre_affichage);
}

void EcranAccueilCampement::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris){
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

EcranAccueilCampement::~EcranAccueilCampement(){
}

void EcranAccueilCampement::obtenirChangement(Observable &obj){
    m_tableau_objets->vider();
    for(auto o : m_controleur->obtenirModele()->obtenirCampement()->obtenirObjets()){
        m_tableau_objets->ajouterLigne(o);
    }

    for(auto o : m_controleur->obtenirModele()->obtenirCampement()->obtenirVivres()){
        m_tableau_objets->ajouterLigne(o);
    }
    m_consoDispo.mettreAJourTexte(TEXTE_CONSOMMATION_DISPONIBLE+std::to_string(m_controleur->obtenirModele()->obtenirCampement()->obtenirValeurNutritiveDisponible()));
    m_consommation.mettreAJourTexte(TEXTE_CONSOMMATION+std::to_string(m_controleur->obtenirModele()->obtenirCampement()->obtenirConsommation()));
    m_nombreObjets.mettreAJourTexte(TEXTE_NOMBRE_OBJETS+std::to_string(m_controleur->obtenirModele()->obtenirCampement()->obtenirVivres().size()+m_controleur->obtenirModele()->obtenirCampement()->obtenirObjets().size()));
}
