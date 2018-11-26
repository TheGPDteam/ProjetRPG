#include "ecranquetecampement.h"

EcranQueteCampement::EcranQueteCampement(Controleur *controleur)
    :
      EcranGeneral (controleur)


{
    coordBoutonCampement = {WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE - 200};
    coordBoutonRetour = {WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE - 300};
    const std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    SDL_Rect rectBoutonCampement = {
        static_cast<Sint16>(coordBoutonCampement.first), static_cast<Sint16>(coordBoutonCampement.second), static_cast<Uint16>(tailleB.first), static_cast<Uint16>(tailleB.second)};

    ajoutBoutonDansMapDeBoutons(new Bouton("Retour Campement",rectBoutonCampement,m_controleur, nullptr,true,
                                           std::make_pair<float,float>(coordBoutonCampement.first+20,coordBoutonCampement.second+15),POLICE_COLLEGED),&ActionsBoutons::boutonCampement);

}

void EcranQueteCampement::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage){
    afficherBoutons(coord_souris, fenetre_affichage);
}

void EcranQueteCampement::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris){
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

void EcranQueteCampement::obtenirChangement(Observable &obj){}
