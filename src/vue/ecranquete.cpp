#include "ecranquete.h"
#include "constantesbouton.h"
#include "bouton.h"
#include <utility>

EcranQuete::EcranQuete(Controleur *controleur) : m_methodeVerificationCliqueSourisSurBouton(&DictionnaireDeBoutons::verificationCliqueSourisSurBouton),
    m_nomFenetre("Repartition des Quetes", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 60)),
    m_controleur {controleur}
{
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2), (HEIGHT_FENETRE_PRINCIPALE)-(HEIGHT_BOUTON_NORMAL)-10);
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Nouvelle Partie", POLICE_COLLEGED, 20, coordB, tailleB, std::make_pair(coordB.first+10,coordB.second+10)), &ActionsBoutons::boutonChoixJoueur);

    m_fondPerso = {20,50,WIDTH_FENETRE_PRINCIPALE-20*2,HEIGHT_FENETRE_PRINCIPALE/2-20*2-10};
    m_fondRecolte = {20,HEIGHT_FENETRE_PRINCIPALE/2+20,WIDTH_FENETRE_PRINCIPALE/2-20*2+10,HEIGHT_FENETRE_PRINCIPALE/2-20*2-HEIGHT_BOUTON_NORMAL};
    m_fondChasse = {WIDTH_FENETRE_PRINCIPALE/2+20-10,HEIGHT_FENETRE_PRINCIPALE/2+20,WIDTH_FENETRE_PRINCIPALE/2-20*2+10,HEIGHT_FENETRE_PRINCIPALE/2-20*2-HEIGHT_BOUTON_NORMAL};
    m_fondDescriptionPerso = {30, 60, WIDTH_FENETRE_PRINCIPALE - 20* 3, 40};
    m_fondDescriptionChasse = {WIDTH_FENETRE_PRINCIPALE/2+20, HEIGHT_FENETRE_PRINCIPALE/2+30, WIDTH_FENETRE_PRINCIPALE/2-20*2-10, 40};
    m_fondDescriptionRecolte = {30, HEIGHT_FENETRE_PRINCIPALE/2+30, WIDTH_FENETRE_PRINCIPALE/2-20*2-10, 40};

    m_CoordNom = std::make_pair(m_fondDescriptionPerso.x + 10, m_fondDescriptionPerso.y + 10);
    m_CoordNiveau = std::make_pair(m_CoordNom.first + 260, m_fondDescriptionPerso.y + 10);
    m_CoordVie = std::make_pair(m_CoordNiveau.first + 120, m_fondDescriptionPerso.y + 10);
    m_CoordIntelligence = std::make_pair(m_CoordVie.first + 70, m_fondDescriptionPerso.y + 10);
    m_CoordForce = std::make_pair(m_CoordIntelligence.first + 220, m_fondDescriptionPerso.y + 10);
    m_CoordVitesse = std::make_pair(m_CoordForce.first + 130, m_fondDescriptionPerso.y + 10);

    m_zoneNomPersonnage = new TexteSDL("Nom", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, m_CoordNom);
    m_zoneNiveauPersonnage = new TexteSDL("Niveau", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, m_CoordNiveau);
    m_zoneViePersonnage = new TexteSDL("Vie", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, m_CoordVie);           // position imprécise **
    m_zoneIntelligencePersonnage = new TexteSDL("Intelligence", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, m_CoordIntelligence);
    m_zoneForcePersonnage = new TexteSDL("Force", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,m_CoordForce );
    m_zoneVitessePersonnage = new TexteSDL("Vitesse", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, m_CoordVitesse);
    m_zoneChasse = new TexteSDL ("Chasse",SDL_Color{255,255,255,255},POLICE_COLLEGED,20,std::make_pair(m_fondDescriptionChasse.x+m_fondDescriptionChasse.w/2-40,m_fondDescriptionChasse.y+10));
    m_zoneRecolte = new TexteSDL ("Recolte",SDL_Color{255,255,255,255},POLICE_COLLEGED,20,std::make_pair(m_fondDescriptionRecolte.x+m_fondDescriptionRecolte.w/2-60,m_fondDescriptionRecolte.y+10));

    Equipe* equipe = m_controleur->obtenirModele()->obtenirJoueur()->obtenirEquipe();
//    Humain* h = new Humain;
//    h->definirNom("nn");
//    equipe->ajouterPersonnage(h);

    for (auto p: equipe->obtenirListePersonnage())
    {
        m_equipe.push_back(dynamic_cast<Humain*>(p));
    }

}
EcranQuete::~EcranQuete(){}


void EcranQuete::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage)
{
    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
    SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));

    SDL_FillRect(fenetre_affichage, &m_fondPerso, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondRecolte, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondChasse, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondDescriptionPerso, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));
    SDL_FillRect(fenetre_affichage, &m_fondDescriptionChasse, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));
    SDL_FillRect(fenetre_affichage, &m_fondDescriptionRecolte, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));


    m_nomFenetre.afficherTexte(fenetre_affichage);
    m_zoneNomPersonnage->afficherTexte(fenetre_affichage);
    m_zoneNiveauPersonnage->afficherTexte(fenetre_affichage);
    m_zoneViePersonnage->afficherTexte(fenetre_affichage);
    m_zoneIntelligencePersonnage->afficherTexte(fenetre_affichage);
    m_zoneForcePersonnage->afficherTexte(fenetre_affichage);
    m_zoneVitessePersonnage->afficherTexte(fenetre_affichage);
    m_zoneChasse->afficherTexte(fenetre_affichage);
    m_zoneRecolte->afficherTexte(fenetre_affichage);
    int i=0;
    for (auto h : m_equipe)
    {
        i=i+1;
        //m_fondDescriptionPerso.x + 10, m_fondDescriptionPerso.y + m_fondDescriptionPerso.h*i));
        TexteSDL tempNomPersonnage(h->obtenirNom(), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordNom.first,m_CoordNom.second+45*i));
        tempNomPersonnage.afficherTexte(fenetre_affichage);
        TexteSDL tempNiveauPersonnage(std::to_string(h->obtenirNiveau().obtenirNiveauActuel()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordNiveau.first,m_CoordNiveau.second+45*i));
        tempNiveauPersonnage.afficherTexte(fenetre_affichage);
        TexteSDL tempViePersonnage(std::to_string(h->obtenirVie()->obtenirValeur()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordVie.first,m_CoordVie.second+45*i));           // position imprécise **
        tempViePersonnage.afficherTexte(fenetre_affichage);
        TexteSDL tempIntelligencePersonnage(std::to_string(h->obtenirIntelligence()->obtenirValeur()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordIntelligence.first,m_CoordIntelligence.second+45*i));
        tempIntelligencePersonnage.afficherTexte(fenetre_affichage);
        TexteSDL tempForcePersonnage(std::to_string(h->obtenirForce()->obtenirValeur()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordForce.first,m_CoordForce.second+45*i));
        tempForcePersonnage.afficherTexte(fenetre_affichage);
        TexteSDL tempVitessePersonnage(std::to_string(h->obtenirVitesse()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordVitesse.first,m_CoordVitesse.second+45*i));
        tempVitessePersonnage.afficherTexte(fenetre_affichage);
    }
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
