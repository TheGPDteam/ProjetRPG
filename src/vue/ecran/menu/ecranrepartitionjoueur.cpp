#include "ecranrepartitionjoueur.h"
#include "utility"

#include "../../interfaceutilisateur/conteneur/bouton/bouton.h"
#include "../../interfaceutilisateur/conteneur/bouton/constantesbouton.h"

const int ESPACE_X_RECTANGLE_OBJET = 20;
const int ESPACE_Y_RECTANGLE_OBJET = 115;
const int LARGEUR_RECTANGLE_PERSONNAGE = WIDTH_FENETRE_PRINCIPALE -  2 * ESPACE_X_RECTANGLE_OBJET;
const int HAUTEUR_RECTANGLE_PERSONNAGE = HEIGHT_FENETRE_PRINCIPALE - 2 * ESPACE_Y_RECTANGLE_OBJET;


RepartitionJoueur::RepartitionJoueur(Humain * h, SDL_Surface *fenetre) :

    m_fenetre{fenetre}

{
    m_rectangleFichePersonnage = {ESPACE_X_RECTANGLE_OBJET, ESPACE_Y_RECTANGLE_OBJET, LARGEUR_RECTANGLE_PERSONNAGE, HAUTEUR_RECTANGLE_PERSONNAGE};
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

    m_zoneQuestion = new TexteSDL("Quelle tache doit-il faire ?", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(m_rectangleFichePersonnage.x + 40, m_rectangleFichePersonnage.y + 350));

    //A SUPPRIMER

    //    m_retour = new Bouton(Normal, true, "Retour", POLICE_COLLEGED, 20,
    //                          std::make_pair(m_rectangleFichePersonnage.x + 60 , m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5),
    //                          std::make_pair(WIDTH_BOUTON_NORMAL , HEIGHT_BOUTON_NORMAL),
    //                          std::make_pair(m_rectangleFichePersonnage.x + 130 , m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ), POLICE_COLLEGED);
    SDL_Rect rect = {m_rectangleFichePersonnage.x + 60 , m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5,
                     WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL};
    m_retour = new Bouton("Retour", rect, NULL, nullptr,
                          true, std::make_pair<float, float>(m_rectangleFichePersonnage.x + 130 , m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ), POLICE_COLLEGED);
    //    m_recolte = new Bouton(Normal, true, "Recolte", POLICE_COLLEGED, 20,
    //                           std::make_pair(m_rectangleFichePersonnage.x + 60 + WIDTH_BOUTON_NORMAL + 20 , m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5),
    //                           std::make_pair(WIDTH_BOUTON_NORMAL , HEIGHT_BOUTON_NORMAL),
    //                           std::make_pair(m_rectangleFichePersonnage.x + 60 + WIDTH_BOUTON_NORMAL + 90, m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ));
    SDL_Rect rect2 = {m_rectangleFichePersonnage.x + 60 + WIDTH_BOUTON_NORMAL + 20 , m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5,
                      WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL};
    m_recolte = new Bouton("Recolte", rect2, NULL, nullptr,
                           true, std::make_pair<float, float>(m_rectangleFichePersonnage.x + 60 + WIDTH_BOUTON_NORMAL + 90, m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ), POLICE_COLLEGED);
    //    m_chasse = new Bouton(Normal, true, "Chasse", POLICE_COLLEGED, 20,
    //                          std::make_pair(m_rectangleFichePersonnage.x + 50 + (WIDTH_BOUTON_NORMAL + 30)*2, m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5),
    //                          std::make_pair(WIDTH_BOUTON_NORMAL , HEIGHT_BOUTON_NORMAL),
    //                          std::make_pair(m_rectangleFichePersonnage.x + 50 + (WIDTH_BOUTON_NORMAL + 30)*2 + 70, m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ));
    SDL_Rect rect3 = {m_rectangleFichePersonnage.x + 50 + (WIDTH_BOUTON_NORMAL + 30)*2, m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5,
                      WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL};
    m_chasse = new Bouton("Chasse", rect3, NULL, nullptr,
                          true, std::make_pair<float, float>(m_rectangleFichePersonnage.x + 50 + (WIDTH_BOUTON_NORMAL + 30)*2 + 70, m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ), POLICE_COLLEGED);

    /*
    SDL_Rect rect = {m_rectangleFichePersonnage.x + 60 , m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5,
                     WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL};
    ajoutBoutonDansMapDeBoutons(new Bouton("Retour", rect, NULL, nullptr,
                                           true, std::make_pair<float, float>(m_rectangleFichePersonnage.x + 130 , m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ), POLICE_COLLEGED), NULL);

    SDL_Rect rect2 = {m_rectangleFichePersonnage.x + 60 + WIDTH_BOUTON_NORMAL + 20 , m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 577,
                      WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL};

    ajoutBoutonDansMapDeBoutons(new Bouton("Recolte", rect2, NULL, nullptr,
                                           true, std::make_pair<float, float>(m_rectangleFichePersonnage.x + 60 + WIDTH_BOUTON_NORMAL + 90, m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ), POLICE_COLLEGED), NULL);

    SDL_Rect rect3 = {m_rectangleFichePersonnage.x + 50 + (WIDTH_BOUTON_NORMAL + 30)*2, m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL - 5,
                      WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL};

    ajoutBoutonDansMapDeBoutons(new Bouton("Chasse", rect3, NULL, nullptr,
                                           true, std::make_pair<float, float>(m_rectangleFichePersonnage.x + 50 + (WIDTH_BOUTON_NORMAL + 30)*2 + 70, m_rectangleFichePersonnage.y + m_rectangleFichePersonnage.h - HEIGHT_BOUTON_NORMAL + 10 ), POLICE_COLLEGED), NULL);
*/

}

void RepartitionJoueur::afficher(){

    SDL_FillRect(m_fenetre, &m_rectangleFichePersonnage, SDL_MapRGB(m_fenetre->format, 200, 200, 200));



    m_zoneNomPersonnage->afficher(m_fenetre);
    m_zonePrenomPersonnage->afficher(m_fenetre);

    m_zoneNiveauPersonnage->afficher(m_fenetre);
    m_zoneForcePersonnage->afficher(m_fenetre);
    m_zoneChassePersonnage->afficher(m_fenetre);
    m_zoneRecoltePersonnage->afficher(m_fenetre);
    m_zoneIntelligencePersonnage->afficher(m_fenetre);
    m_zoneVitessePersonnage->afficher(m_fenetre);
    m_zoneDescArmePersonnage->afficher(m_fenetre);
    m_zoneNomArmePersonnage->afficher(m_fenetre);
    m_zoneDegatsArmePersonnage->afficher(m_fenetre);
    m_zoneQuestion->afficher(m_fenetre);

    m_recolte->afficher(m_fenetre);
    m_retour->afficher(m_fenetre);
    m_chasse->afficher(m_fenetre);

    SDL_Flip(m_fenetre);
    // afficherBoutons(coord_souris, m_fenetre);


}

int  RepartitionJoueur::affecter(){
    int affectation = -1;
    bool quitter = false;
    while(!quitter){
        afficher();
        affectation = gestionDesEvenements();
        if(affectation != RIEN)
            quitter = true;

    }
    return affectation;
}

int RepartitionJoueur::gestionDesEvenements(){

    SDL_Event evenements;
    int repartition = RIEN;
    while(SDL_PollEvent(&evenements))
    {
        switch(evenements.type)
        {
        case SDL_QUIT:
            SDL_Quit();
            break;

        case SDL_MOUSEBUTTONUP:
            if(evenements.button.button == SDL_BUTTON_LEFT)
            {

                if(m_retour->contient(std::pair<int,int> (evenements.button.x, evenements.button.y))){
                    repartition = RETOUR;
                    break;
                }
                else if(m_recolte->contient(std::pair<int,int> (evenements.button.x, evenements.button.y))){
                    repartition = RECOLTE;
                    break;
                }
                else if(m_chasse->contient(std::pair<int,int> (evenements.button.x, evenements.button.y))){
                    repartition = CHASSE;
                    break;
                }
            }
            break;

        default:
            break;

        }
    }
    return repartition;
}



RepartitionJoueur::~RepartitionJoueur(){

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
