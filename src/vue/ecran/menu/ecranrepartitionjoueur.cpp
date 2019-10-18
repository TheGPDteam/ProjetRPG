#include "ecranrepartitionjoueur.h"
#include "utility"

#include "bouton.h"
#include "constantesbouton.h"

const int ESPACE_X_RECTANGLE_OBJET = 20;
const int ESPACE_Y_RECTANGLE_OBJET = 115;
const int LARGEUR_RECTANGLE_PERSONNAGE = WIDTH_FENETRE_PRINCIPALE -  2 * ESPACE_X_RECTANGLE_OBJET;
const int HAUTEUR_RECTANGLE_PERSONNAGE = HEIGHT_FENETRE_PRINCIPALE - 2 * ESPACE_Y_RECTANGLE_OBJET;


EcranRepartitionJoueur::EcranRepartitionJoueur(Controleur * controleur) :
    EcranGeneral(controleur), m_etatAfficher(false)
{
    m_rectangleFichePersonnage = {ESPACE_X_RECTANGLE_OBJET, ESPACE_Y_RECTANGLE_OBJET, LARGEUR_RECTANGLE_PERSONNAGE, HAUTEUR_RECTANGLE_PERSONNAGE};

    //A SUPPRIMER

    //    m_retour = new Bouton(Normal, true, "Retour", POLICE_COLLEGED, 20,
    //                          std::make_pair(m_rectangleFichePersonnage.x + 60 , m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5),
    //                          std::make_pair(WIDTH_BOUTON_NORMAL , HEIGHT_BOUTON_NORMAL),
    //                          std::make_pair(m_rectangleFichePersonnage.x + 130 , m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ), POLICE_COLLEGED);
    SDL_Rect rect = {m_rectangleFichePersonnage.x + 40 + (WIDTH_BOUTON_NORMAL + 60)*2 , m_rectangleFichePersonnage.y + HEIGHT_BOUTON_NORMAL - 20,
                     WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL};
    m_retour = new Bouton("Retour", rect, m_controleur, nullptr,
                          true, /*std::make_pair<float, float>(m_rectangleFichePersonnage.x + 130 , m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ),*/ POLICE_COLLEGED);

    SDL_Rect rect2 = {m_rectangleFichePersonnage.x + 60 + 20 , m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5,
                      WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL};
    m_recolte = new Bouton("Recolte", rect2, m_controleur, nullptr,
                           true, /*std::make_pair<float, float>(m_rectangleFichePersonnage.x + 60 + WIDTH_BOUTON_NORMAL + 90, m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ),*/ POLICE_COLLEGED);


    SDL_Rect rect3 = {m_rectangleFichePersonnage.x + 60 + (WIDTH_BOUTON_NORMAL + 50), m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5,
                      WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL};
    m_chasse = new Bouton("Chasse", rect3, m_controleur, nullptr,
                          true, /*std::make_pair<float, float>(m_rectangleFichePersonnage.x + 50 + (WIDTH_BOUTON_NORMAL + 30)*2 + 70, m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ),*/ POLICE_COLLEGED);


    SDL_Rect rect4 = {m_rectangleFichePersonnage.x + 60 + (WIDTH_BOUTON_NORMAL + 40)*2, m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5,
                      WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL};
    m_campement = new Bouton("Campement", rect4, m_controleur, nullptr,
                             m_controleur->obtenirModele()->obtenirJoueur()->obtenirQuetePrincipale().partiesBusReunies(), /*std::make_pair<float, float>(m_rectangleFichePersonnage.x + 40 + (WIDTH_BOUTON_NORMAL + 60)*2 + 50, m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ),*/ POLICE_COLLEGED);
    ajoutBoutonDansMapDeBoutons(m_retour, nullptr);
    ajoutBoutonDansMapDeBoutons(m_recolte, nullptr);
    ajoutBoutonDansMapDeBoutons(m_chasse, nullptr);
    ajoutBoutonDansMapDeBoutons(m_campement, nullptr);
    m_zoneNomPersonnage = new TexteSDL("Nom : ", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 20));
    m_zonePrenomPersonnage = new TexteSDL("Prenom : " , SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 350, m_rectangleFichePersonnage.y + 20));

    m_zoneNiveauPersonnage = new TexteSDL("Niveau : ", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 70));

    m_zoneForcePersonnage = new TexteSDL("Force : ", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 100));
    m_zoneIntelligencePersonnage = new TexteSDL("Intelligence : ", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 130));
    m_zoneVitessePersonnage = new TexteSDL("Vitesse : " , SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 160));

    m_zoneChassePersonnage = new TexteSDL("Chasse : " , SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 450, m_rectangleFichePersonnage.y + 130));
    m_zoneRecoltePersonnage = new TexteSDL("Recolte : " , SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 450, m_rectangleFichePersonnage.y + 160));
    m_zoneCampementPersonnage = new TexteSDL("Campement : ", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 450, m_rectangleFichePersonnage.y + 190));


    m_zoneNomArmePersonnage = new TexteSDL("Arme : " , SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 240));
    m_zoneDescArmePersonnage = new TexteSDL("Description : " , SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 270));
    m_zoneDegatsArmePersonnage = new TexteSDL("Degats : ", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 50, m_rectangleFichePersonnage.y + 300));
    m_zoneQuestion = new TexteSDL("Quelle tache doit-il faire ?", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 40, m_rectangleFichePersonnage.y + 350));

}

void EcranRepartitionJoueur::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage){

    SDL_FillRect(fenetre_affichage, &m_rectangleFichePersonnage, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));

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

    //    m_recolte->afficher(fenetre_affichage);
    //    m_retour->afficher(fenetre_affichage);
    //    m_chasse->afficher(fenetre_affichage);
    //    m_campement->afficher(fenetre_affichage);

    afficherBoutons(coord_souris, fenetre_affichage);


}
void EcranRepartitionJoueur::definirHumain(Humain * h){
    m_humain = h;
    m_zoneNomPersonnage->mettreAJourTexte("Nom : " + h->obtenirNom());
    m_zonePrenomPersonnage->mettreAJourTexte("Prenom : " + h->obtenirPrenom());
    m_zoneNiveauPersonnage->mettreAJourTexte("Niveau : " + std::to_string(h->obtenirNiveau().obtenirNiveauActuel()));
    m_zoneForcePersonnage->mettreAJourTexte("Force : " + std::to_string(h->obtenirForce()->obtenirValeur()));
    m_zoneIntelligencePersonnage->mettreAJourTexte("Intelligence : " + std::to_string(h->obtenirIntelligence()->obtenirValeur()));
    m_zoneVitessePersonnage->mettreAJourTexte("Vitesse : " + std::to_string(h->obtenirVitesse()));
    m_zoneChassePersonnage->mettreAJourTexte("Chasse : " + std::to_string(h->obtenirChasse().obtenirValeur()));
    m_zoneRecoltePersonnage->mettreAJourTexte("Recolte : " + std::to_string(h->obtenirRecolte().obtenirValeur()));
    m_zoneCampementPersonnage->mettreAJourTexte("Campement : " + std::to_string(h->obtenirCampement().obtenirValeur()));

    m_zoneNomArmePersonnage->mettreAJourTexte("Arme : " + h->obtenirArme()->obtenirNom());
    m_zoneDescArmePersonnage->mettreAJourTexte("Description : " + h->obtenirArme()->obtenirDescription());
    m_zoneDegatsArmePersonnage->mettreAJourTexte("Degats : " + std::to_string(h->obtenirArme()->obtenirDegats()));

    m_etatAfficher =true;
    Campement * c = m_controleur->obtenirModele()->obtenirCampement();
    Equipe *equipeArriver = c->obtenirEquipePersonnage(h);
    remiseAZeroBoutons();
    m_chasse->definirCliquable(equipeArriver != c->obtenirEquipeChasse());
    m_recolte->definirCliquable(equipeArriver != c->obtenirEquipeRecolte());
//    m_campement->definirCliquable(equipeArriver != c->obtenirEquipeCampement());
}

void EcranRepartitionJoueur::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris){

    SDL_Event evenements;
    AFFECTATION repartition = RIEN;
    while (SDL_PollEvent(&evenements)){
        switch (evenements.type){
        case SDL_QUIT:

//            SDL_Quit();
            break;

        case SDL_MOUSEBUTTONUP:
            if (evenements.button.button == SDL_BUTTON_LEFT){

                if (m_retour->contient(std::pair<int,int> (evenements.button.x, evenements.button.y))){
                    repartition = RETOUR;
                } else if (m_recolte->contient(std::pair<int,int> (evenements.button.x, evenements.button.y))){
                    repartition = RECOLTE;
                } else if (m_chasse->contient(std::pair<int,int> (evenements.button.x, evenements.button.y))){
                    repartition = CHASSE;
                } else if (m_campement->contient(std::pair<int,int> (evenements.button.x, evenements.button.y))){
                    repartition = CAMPEMENT;
                }

                if (repartition != RIEN){
                    m_etatAfficher = false;

                    if(repartition != RETOUR)    gestionRepartion(repartition);
                }
            }
            break;

        default:
            break;

        }
        coord_souris.first = evenements.button.x;
        coord_souris.second = evenements.button.y;
    }
}

void EcranRepartitionJoueur::gestionRepartion(AFFECTATION affectation){
    Campement *c  =  m_controleur->obtenirModele()->obtenirCampement();
    c->supprimerPersonnage(m_humain);
    if (affectation == CHASSE){
        c->obtenirEquipeChasse()->ajouterPersonnage(m_humain);
    } else if (affectation == RECOLTE){
        c->obtenirEquipeRecolte()->ajouterPersonnage(m_humain);
    } else if (affectation == CAMPEMENT){
        c->obtenirEquipeCampement()->ajouterPersonnage(m_humain);
    }
}

EcranRepartitionJoueur::~EcranRepartitionJoueur(){

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
    if (m_zoneCampementPersonnage != nullptr)
        delete m_zoneCampementPersonnage;
    if (m_zoneNomArmePersonnage != nullptr)
        delete m_zoneNomArmePersonnage;
    if (m_zoneDegatsArmePersonnage != nullptr)
        delete m_zoneDegatsArmePersonnage;
    if (m_zoneDescArmePersonnage != nullptr)
        delete m_zoneDescArmePersonnage;


}

bool EcranRepartitionJoueur::obtenirEtatAfficher(){
    return m_etatAfficher;
}

void EcranRepartitionJoueur::obtenirChangement(Observable &obj){

}
