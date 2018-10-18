#include "ecrannom.h"

EcranNom::EcranNom(Controleur* controleur) :
    EcranGeneral{controleur},
    m_nom_fenetre("Selection d'un nom de personnage", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20,
                                        std::make_pair(0,HEIGHT_FENETRE_PRINCIPALE/4), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 40)),
                       m_label("Tapez votre nom : ", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20,
                                             std::make_pair(0,(HEIGHT_FENETRE_PRINCIPALE/2) - 50), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 40)),
                       m_s{new Saisir()}
{
     ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Commencer", POLICE_COLLEGED, 20, std::make_pair(390,3*(HEIGHT_FENETRE_PRINCIPALE/4) - 70), std::make_pair(200,50),std::make_pair(390 + 45, 3*(HEIGHT_FENETRE_PRINCIPALE/4) - 55)), &ActionsBoutons::boutonChoixPersonnage); // Pk taille = position texte sdl ?
}

const int CONTOUR_ARRIERE_PLAN = HEIGHT_FENETRE_PRINCIPALE/4;

void EcranNom::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage){

    afficherFondEcran(fenetre_affichage);

    SDL_Rect zone = {CONTOUR_ARRIERE_PLAN,CONTOUR_ARRIERE_PLAN,WIDTH_FENETRE_PRINCIPALE-(2*CONTOUR_ARRIERE_PLAN), HEIGHT_FENETRE_PRINCIPALE-(2*CONTOUR_ARRIERE_PLAN)};
    SDL_FillRect(fenetre_affichage, &zone, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));

    m_nom_fenetre.afficherTexte(fenetre_affichage);
    m_label.afficherTexte(fenetre_affichage);

    m_s->afficher(fenetre_affichage);
    afficherBoutons(coord_souris, fenetre_affichage);
}

void EcranNom::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris){

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
        case SDL_KEYDOWN:

            if((std::string)SDL_GetKeyName(evenements.key.keysym.sym) == "backspace"){
                m_s->enleverChar();
            }
            else if(isalpha(*SDL_GetKeyName(evenements.key.keysym.sym)) && ((std::string)(SDL_GetKeyName(evenements.key.keysym.sym))).size() == 1 ){
                    m_s->ajouterChar(SDL_GetKeyName(evenements.key.keysym.sym));
                }
            m_controleur->obtenirModele()->obtenirJoueur()->definirNom(m_s->obtenirBuffer());
            break;

        default:
            coord_souris.first = evenements.button.x;
            coord_souris.second = evenements.button.y;
            break;

        }
    }
}

void EcranNom::obtenirChangement(Observable &obj){

}


EcranNom::~EcranNom(){
    delete m_s;
}
