#include "ecrannom.h"

EcranNom::EcranNom(Controleur* controleur) :
    EcranGeneral{controleur},
    m_nom_fenetre("Selection d'un nom de personnage", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,
                                        std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 60)),
                       m_label("Tapez votre nom : ", SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20,
                                             std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 300)),
                       s{new Saisir()}
{
     ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Commencer", POLICE_COLLEGED, 20, std::make_pair(390,500), std::make_pair(200,50),std::make_pair(390 + 25, 500 + 10)), &ActionsBoutons::boutonChoixPersonnage); // Pk taille = position texte sdl ?

}

void EcranNom::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage){

    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
    SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));

    m_nom_fenetre.afficherTexte(fenetre_affichage);
    m_label.afficherTexte(fenetre_affichage);

    s->afficher(fenetre_affichage);
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
                std::cout << coord_souris.first << "  " << coord_souris.second << std::endl;
                coord_souris.first = evenements.button.x;
                coord_souris.second = evenements.button.y;
                std::cout << coord_souris.first << "  " << coord_souris.second << std::endl;
            }
            break;
        case SDL_KEYDOWN:

            if((std::string)SDL_GetKeyName(evenements.key.keysym.sym) == "backspace"){
                s->enleverChar();
            }
            else if(isalpha(*SDL_GetKeyName(evenements.key.keysym.sym)) && ((std::string)(SDL_GetKeyName(evenements.key.keysym.sym))).size() == 1 ){ // Autre que les lettre de l'alpha ont même char acsii
                    s->ajouterChar(SDL_GetKeyName(evenements.key.keysym.sym));
                }
            m_controleur->obtenirModele()->obtenirJoueur()->definirNom(s->obtenirBuffer());
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
    delete s;
}
