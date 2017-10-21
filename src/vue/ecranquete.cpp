#include "ecranquete.h"
#include "constantesbouton.h"
#include "bouton.h"
#include <utility>

EcranQuete::EcranQuete() : m_methodeVerificationCliqueSourisSurBouton(&DictionnaireDeBoutons::verificationCliqueSourisSurBouton),
    m_nomFenetre("Repartition des Quetes", SDL_Color{255,255,255}, POLICE_COLLEGED, 20,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 60))
{
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2), (HEIGHT_FENETRE_PRINCIPALE)-(HEIGHT_BOUTON_NORMAL)-10);
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Nouvelle Partie", POLICE_COLLEGED, 20, coordB, tailleB), &ActionsBoutons::boutonJeuPrincipal);


    m_fondPerso = {20,50,WIDTH_FENETRE_PRINCIPALE-20*2,HEIGHT_FENETRE_PRINCIPALE/2-20*2-10};
    m_fondRecolte = {20,HEIGHT_FENETRE_PRINCIPALE/2+20,WIDTH_FENETRE_PRINCIPALE/2-20*2+10,HEIGHT_FENETRE_PRINCIPALE/2-20*2-HEIGHT_BOUTON_NORMAL};
    m_fondChasse = {WIDTH_FENETRE_PRINCIPALE/2+20-10,HEIGHT_FENETRE_PRINCIPALE/2+20,WIDTH_FENETRE_PRINCIPALE/2-20*2+10,HEIGHT_FENETRE_PRINCIPALE/2-20*2-HEIGHT_BOUTON_NORMAL};
    m_fondDescription = {m_fondPerso.x + 10, m_fondPerso.y + 10, WIDTH_FENETRE_PRINCIPALE - m_fondPerso.x * 3, 40};

    m_zoneNomPersonnage = new TexteSDL("Nom", SDL_Color{255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_fondDescription.x + 10, m_fondDescription.y + 10));
    m_zoneNiveauPersonnage = new TexteSDL("Niveau", SDL_Color{255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_fondDescription.x + 90, m_fondDescription.y + 10));
    m_zoneViePersonnage = new TexteSDL("Vie", SDL_Color{255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_fondDescription.x + 210, m_fondDescription.y + 10));           // position imprécise **
    m_zoneIntelligencePersonnage = new TexteSDL("Intelligence", SDL_Color{255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_fondDescription.x + 290, m_fondDescription.y + 10));
    m_zoneForcePersonnage = new TexteSDL("Force", SDL_Color{255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_fondDescription.x + 510, m_fondDescription.y + 10));
    m_zoneVitessePersonnage = new TexteSDL("Vitesse", SDL_Color{255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_fondDescription.x + 640, m_fondDescription.y + 10));


}
EcranQuete::~EcranQuete(){}


void EcranQuete::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage)
{
    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
    SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));

    SDL_FillRect(fenetre_affichage, &m_fondPerso, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondRecolte, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondChasse, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondDescription, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));


    m_nomFenetre.afficherTexte(fenetre_affichage);
    m_zoneNomPersonnage->afficherTexte(fenetre_affichage);
    m_zoneNiveauPersonnage->afficherTexte(fenetre_affichage);
    m_zoneViePersonnage->afficherTexte(fenetre_affichage);
    m_zoneIntelligencePersonnage->afficherTexte(fenetre_affichage);
    m_zoneForcePersonnage->afficherTexte(fenetre_affichage);
    m_zoneVitessePersonnage->afficherTexte(fenetre_affichage);


    afficherBoutons(coord_souris, fenetre_affichage);
}


void EcranQuete::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris)
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

void EcranQuete::obtenirChangement(Observable &obj){}
