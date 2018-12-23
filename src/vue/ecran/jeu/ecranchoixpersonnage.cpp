#include "ecranchoixpersonnage.h"
#include "utility"

#include "../../interfaceutilisateur/conteneur/bouton/bouton.h"
#include "../../interfaceutilisateur/conteneur/bouton/constantesbouton.h"

const int ESPACE_X_RECTANGLE_PERSONNAGE= 20;
const int ESPACE_Y_RECTANGLE_PERSONNAGE = 115;
const int LARGEUR_RECTANGLE_PERSONNAGE = WIDTH_FENETRE_PRINCIPALE -  2 * ESPACE_X_RECTANGLE_PERSONNAGE;
const int HAUTEUR_RECTANGLE_PERSONNAGE = HEIGHT_FENETRE_PRINCIPALE - 2 * ESPACE_Y_RECTANGLE_PERSONNAGE;

EcranChoixPersonnage::EcranChoixPersonnage(Controleur* controleur):
    EcranGeneral{controleur},
    m_nomFenetre("Arrivee d'un survivant", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 30,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 100))
{
    m_rectangleFichePersonnage = {ESPACE_X_RECTANGLE_PERSONNAGE, ESPACE_Y_RECTANGLE_PERSONNAGE, LARGEUR_RECTANGLE_PERSONNAGE, HAUTEUR_RECTANGLE_PERSONNAGE};


    // Humain* h = m_controleur->journeeSuivante();

    m_zoneNomPersonnage = new TexteSDL("", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 20));
    m_zonePrenomPersonnage = new TexteSDL("", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 350, m_rectangleFichePersonnage.y + 20));

    m_zoneNiveauPersonnage = new TexteSDL("", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 70));

    m_zoneForcePersonnage = new TexteSDL("", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 100));
    m_zoneIntelligencePersonnage = new TexteSDL("", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 130));
    m_zoneVitessePersonnage = new TexteSDL("", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 160));

    m_zoneChassePersonnage = new TexteSDL("", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 450, m_rectangleFichePersonnage.y + 100));
    m_zoneRecoltePersonnage = new TexteSDL("", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 450, m_rectangleFichePersonnage.y + 130));
    m_zoneCampementPersonnage = new TexteSDL("", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 450, m_rectangleFichePersonnage.y + 160));

    m_zoneNomArmePersonnage = new TexteSDL("", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 240));
    //m_zoneDescArmePersonnage = new TexteSDL("", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 270));
    m_zoneDescArmePersonnage = new ZoneTexte(POLICE_COLLEGED, 20,/* std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 270),*/
                                             SDL_Rect{m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 270, WIDTH_FENETRE_PRINCIPALE - (m_rectangleFichePersonnage.x + 50), 21},
                                             " ",SDL_Color{0,0,0,0}, COMPORTEMENT_TEXTE::REDIMENTIONNE, ALIGNEMENT_TEXTE::GAUCHE);
    m_zoneDegatsArmePersonnage = new TexteSDL("", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 300));

    m_zoneQuestion = new TexteSDL("Voulez vous accepter ce survivant ?", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 400, m_rectangleFichePersonnage.y + 350));
    /* A SUPPRIMER
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
                                */

    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2)+ 50  , (HEIGHT_FENETRE_PRINCIPALE/2)-(HEIGHT_BOUTON_NORMAL/2)+ 185 );
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);
    SDL_Rect rect = {coordB.first, coordB.second, tailleB.first, tailleB.second};
    ajoutBoutonDansMapDeBoutons(new Bouton("Oui", rect, m_controleur, nullptr,
                                           true, /*std::make_pair<float, float>(coordB.first+20,coordB.second+15),*/ POLICE_COLLEGED), &ActionsBoutons::boutonQueteAcceptation);

    coordB.first+=250;
    SDL_Rect rect2 = {coordB.first, coordB.second, tailleB.first, tailleB.second};

    ajoutBoutonDansMapDeBoutons(new Bouton("Non", rect2, m_controleur, nullptr,
                                           true, /*std::make_pair<float, float>(coordB.first+20,coordB.second+15),*/ POLICE_COLLEGED), &ActionsBoutons::boutonQueteRefus);
}

void EcranChoixPersonnage::mettreAJourInformations(){
    Humain *h = m_controleur->obtenirModele()->obtenirNouvelArrivant();
    m_zoneNomPersonnage->mettreAJourTexte("Nom : " + h->obtenirNom());
    m_zonePrenomPersonnage->mettreAJourTexte("Prenom : " + h->obtenirPrenom());
    m_zoneNiveauPersonnage->mettreAJourTexte("Niveau : " + std::to_string(h->obtenirNiveau().obtenirNiveauActuel()));
    m_zoneForcePersonnage->mettreAJourTexte("Force : " + std::to_string(h->obtenirForce()->obtenirValeur()));
    m_zoneChassePersonnage->mettreAJourTexte("Chasse : " + std::to_string(h->obtenirChasse().obtenirValeur()));
    m_zoneRecoltePersonnage->mettreAJourTexte("Recolte : " + std::to_string(h->obtenirRecolte().obtenirValeur()));
    m_zoneCampementPersonnage->mettreAJourTexte("Campement : " + std::to_string(h->obtenirCampement().obtenirValeur()));
    m_zoneIntelligencePersonnage->mettreAJourTexte("Intelligence : " + std::to_string(h->obtenirIntelligence()->obtenirValeur()));
    m_zoneVitessePersonnage->mettreAJourTexte("Vitesse : " + std::to_string(h->obtenirVitesse()));
    m_zoneDescArmePersonnage->mettreAJourTexte("Description : " + h->obtenirArme()->obtenirDescription());
    m_zoneNomArmePersonnage->mettreAJourTexte("Arme : " + h->obtenirArme()->obtenirNom());
    m_zoneDegatsArmePersonnage->mettreAJourTexte("Degats : " + std::to_string(h->obtenirArme()->obtenirDegats()));
}

void EcranChoixPersonnage::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage){

    //    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
    //    SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));

    afficherFondEcran(fenetre_affichage);
    SDL_FillRect(fenetre_affichage, &m_rectangleFichePersonnage, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));

    m_nomFenetre.afficher(fenetre_affichage);
    m_zoneNomPersonnage->afficher(fenetre_affichage);
    m_zonePrenomPersonnage->afficher(fenetre_affichage);
    m_zoneNiveauPersonnage->afficher(fenetre_affichage);
    m_zoneForcePersonnage->afficher(fenetre_affichage);
    m_zoneChassePersonnage->afficher(fenetre_affichage);
    m_zoneRecoltePersonnage->afficher(fenetre_affichage);
    m_zoneCampementPersonnage->afficher(fenetre_affichage);
    m_zoneIntelligencePersonnage->afficher(fenetre_affichage);
    m_zoneVitessePersonnage->afficher(fenetre_affichage);
    m_zoneDescArmePersonnage->afficher(fenetre_affichage);
    m_zoneNomArmePersonnage->afficher(fenetre_affichage);
    m_zoneDegatsArmePersonnage->afficher(fenetre_affichage);
    m_zoneQuestion->afficher(fenetre_affichage);

    //A SUPPRIMER
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
    if(m_controleur->obtenirModele()->obtenirNouvelArrivant()!= nullptr)
        mettreAJourInformations();
}


EcranChoixPersonnage::~EcranChoixPersonnage(){
    if(m_zonePrenomPersonnage != nullptr)       delete m_zonePrenomPersonnage;
    if(m_zoneNomPersonnage != nullptr)          delete m_zoneNomPersonnage;
    if(m_zoneForcePersonnage != nullptr)        delete m_zoneForcePersonnage;
    if(m_zoneIntelligencePersonnage != nullptr) delete m_zoneIntelligencePersonnage;
    if(m_zoneVitessePersonnage != nullptr)      delete m_zoneVitessePersonnage;
    if (m_zoneChassePersonnage != nullptr)      delete m_zoneChassePersonnage;
    if (m_zoneRecoltePersonnage != nullptr)     delete m_zoneRecoltePersonnage;
    if (m_zoneCampementPersonnage != nullptr)      delete m_zoneCampementPersonnage;
    if(m_zoneNiveauPersonnage != nullptr)       delete m_zoneNiveauPersonnage;
    if (m_zoneNomArmePersonnage != nullptr)     delete m_zoneNomArmePersonnage;
    if (m_zoneDescArmePersonnage != nullptr)    delete m_zoneDescArmePersonnage;
    if (m_zoneDegatsArmePersonnage != nullptr)  delete m_zoneDegatsArmePersonnage;
    if (m_zoneQuestion!= nullptr)               delete m_zoneQuestion;
}
