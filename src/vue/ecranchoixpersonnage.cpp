#include "ecranchoixpersonnage.h"
#include "utility"

#include "bouton.h"
#include "constantesbouton.h"

const int ESPACE_X_RECTANGLE_PERSONNAGE = 20;
const int ESPACE_Y_RECTANGLE_PERSONNAGE = 115;
const int LARGEUR_RECTANGLE_PERSONNAGE = WIDTH_FENETRE_PRINCIPALE -  2 * ESPACE_X_RECTANGLE_PERSONNAGE;
const int HAUTEUR_RECTANGLE_PERSONNAGE = HEIGHT_FENETRE_PRINCIPALE - 2 * ESPACE_Y_RECTANGLE_PERSONNAGE;

EcranChoixPersonnage::EcranChoixPersonnage(Controleur* controleur):
    EcranGeneral{controleur},
    m_nomFenetre("Arrivee d'un survivant", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 30,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 100))
{
    m_rectangleFichePersonnage = {ESPACE_X_RECTANGLE_PERSONNAGE, ESPACE_Y_RECTANGLE_PERSONNAGE, LARGEUR_RECTANGLE_PERSONNAGE, HAUTEUR_RECTANGLE_PERSONNAGE};


    Humain* h = m_controleur->journeeSuivante();

    m_zoneNomPersonnage = new TexteSDL("Nom : " + h->obtenirNom(), SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 20));
    m_zonePrenomPersonnage = new TexteSDL("Prenom : " + h->obtenirPrenom(), SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 350, m_rectangleFichePersonnage.y + 20));

    m_zoneNiveauPersonnage = new TexteSDL("Niveau : " + std::to_string(h->obtenirNiveau().obtenirNiveauActuel()), SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 70));

    m_zoneForcePersonnage = new TexteSDL("Force : " + std::to_string(h->obtenirForce()->obtenirValeur()), SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 100));
    m_zoneIntelligencePersonnage = new TexteSDL("Intelligence : " + std::to_string(h->obtenirIntelligence()->obtenirValeur()), SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 130));
    m_zoneVitessePersonnage = new TexteSDL("Vitesse : " + std::to_string(h->obtenirVitesse()), SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 160));

    m_zoneChassePersonnage = new TexteSDL("Chasse : " + std::to_string(h->obtenirChasse().obtenirValeur()), SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 450, m_rectangleFichePersonnage.y + 130));
    m_zoneRecoltePersonnage = new TexteSDL("Recolte : " + std::to_string(h->obtenirRecolte().obtenirValeur()), SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 450, m_rectangleFichePersonnage.y + 160));

    m_zoneNomArmePersonnage = new TexteSDL("Arme : " + h->obtenirArme()->obtenirNom(), SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 210));
    m_zoneDescArmePersonnage = new TexteSDL("Description : " + h->obtenirArme()->obtenirDescription(), SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 240));
    m_zoneDegatsArmePersonnage = new TexteSDL("Degats : " + std::to_string(h->obtenirArme()->obtenirDegats()), SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 270));

    m_zoneQuestion = new TexteSDL("Voulez vous accepter ce survivant ?", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 400, m_rectangleFichePersonnage.y + 350));

    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Oui", POLICE_COLLEGED, 20,
                                           std::make_pair(WIDTH_FENETRE_PRINCIPALE - WIDTH_BOUTON_NORMAL - 70 ,
                                                          m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5),
                                           std::make_pair(WIDTH_BOUTON_NORMAL / 2 , HEIGHT_BOUTON_NORMAL),
                                           std::make_pair(WIDTH_FENETRE_PRINCIPALE - WIDTH_BOUTON_NORMAL / 2 - 90,
                                                          m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 )),
                                &ActionsBoutons::boutonQueteAcceptation);  // PRENDRE EN COMPTE LE CHOIX
    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Non", POLICE_COLLEGED, 20,
                                           std::make_pair(WIDTH_FENETRE_PRINCIPALE - WIDTH_BOUTON_NORMAL * 2 - 90,
                                                          m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5),
                                           std::make_pair(WIDTH_BOUTON_NORMAL / 2 , HEIGHT_BOUTON_NORMAL),
                                           std::make_pair(WIDTH_FENETRE_PRINCIPALE - WIDTH_BOUTON_NORMAL * 3./2. - 110 ,
                                                          m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10)),
                                &ActionsBoutons::boutonQueteRefus);
}

void EcranChoixPersonnage::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage){

//    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
//    SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));

    afficherFondEcran(fenetre_affichage);
    SDL_FillRect(fenetre_affichage, &m_rectangleFichePersonnage, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));


    m_nomFenetre.afficherTexte(fenetre_affichage);
    m_zoneNomPersonnage->afficherTexte(fenetre_affichage);
    m_zonePrenomPersonnage->afficherTexte(fenetre_affichage);
    m_zoneNiveauPersonnage->afficherTexte(fenetre_affichage);
    m_zoneForcePersonnage->afficherTexte(fenetre_affichage);
    m_zoneChassePersonnage->afficherTexte(fenetre_affichage);
    m_zoneRecoltePersonnage->afficherTexte(fenetre_affichage);
    m_zoneIntelligencePersonnage->afficherTexte(fenetre_affichage);
    m_zoneVitessePersonnage->afficherTexte(fenetre_affichage);
    m_zoneDescArmePersonnage->afficherTexte(fenetre_affichage);
    m_zoneNomArmePersonnage->afficherTexte(fenetre_affichage);
    m_zoneDegatsArmePersonnage->afficherTexte(fenetre_affichage);
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
    if(m_zoneForcePersonnage != nullptr)
        delete m_zoneForcePersonnage;
    if(m_zoneNomPersonnage != nullptr)
        delete m_zoneNomPersonnage;
    if(m_zonePrenomPersonnage != nullptr)
        delete m_zonePrenomPersonnage;
    if(m_zoneForcePersonnage != nullptr)
        delete m_zoneForcePersonnage;
    if(m_zoneIntelligencePersonnage != nullptr)
        delete m_zoneIntelligencePersonnage;
    if(m_zoneVitessePersonnage != nullptr)
        delete m_zoneVitessePersonnage;
    if (m_zoneChassePersonnage != nullptr)
        delete m_zoneChassePersonnage;
    if (m_zoneRecoltePersonnage != nullptr)
        delete m_zoneRecoltePersonnage;
    if (m_zoneNomArmePersonnage != nullptr)
        delete m_zoneNomArmePersonnage;
    if (m_zoneDegatsArmePersonnage != nullptr)
        delete m_zoneDegatsArmePersonnage;
    if (m_zoneDescArmePersonnage != nullptr)
        delete m_zoneDescArmePersonnage;


}
