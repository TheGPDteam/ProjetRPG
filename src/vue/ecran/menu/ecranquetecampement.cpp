#include "ecranquetecampement.h"

EcranQueteCampement::EcranQueteCampement(Controleur *controleur)
    : EcranGeneral (controleur),
      m_spriteRoue{new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{64,128,128,128},SDL_Rect{0,448,128,128}}},
      m_spriteHuile{new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{448+30,128,128,128},
                    SDL_Rect{384,448,128,128}}},
      m_spriteEssence{new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{320+20,128,128,128},
                      SDL_Rect{256,448,128,128}}},
      m_spriteMoteur{new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{192+10,128,128,128},
                     SDL_Rect{128,448,128,128}}}
{
    coordBoutonCampement = {WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE - 200};
    coordBoutonRetour = {WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE - 300};
    const std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    SDL_Rect rectBoutonCampement = {
        static_cast<Sint16>(coordBoutonCampement.first), static_cast<Sint16>(coordBoutonCampement.second), static_cast<Uint16>(tailleB.first), static_cast<Uint16>(tailleB.second)};

    ajoutBoutonDansMapDeBoutons(new Bouton("Retour Campement",rectBoutonCampement,m_controleur, nullptr,true,
                                           POLICE_COLLEGED),&ActionsBoutons::boutonCampement);

    m_fond = SDL_LoadBMP("../rsc/sprites/bus.bmp");
}

void EcranQueteCampement::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage){
    afficherFondEcran(fenetre_affichage);
    afficherBoutons(coord_souris, fenetre_affichage);
    m_spriteRoue->afficher(fenetre_affichage);
    m_spriteMoteur->afficher(fenetre_affichage);
    m_spriteEssence->afficher(fenetre_affichage);
    m_spriteHuile->afficher(fenetre_affichage);
}

void EcranQueteCampement::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris){
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
            }
            break;

        default:
            coord_souris.first = evenements.button.x;
            coord_souris.second = evenements.button.y;
            break;

        }
    }
}

void EcranQueteCampement::obtenirChangement(Observable &obj){
//    m_tableauEquipe->vider();
//    m_tableauEquipe->ajouterLigne(m_controleur->obtenirModele()->obtenirCampement());
}
