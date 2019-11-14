#include "ecranquetecampement.h"
const SDL_Rect RECT_MOTEUR_GRIS = {770,448,128,128};
const SDL_Rect RECT_HUILE_GRIS = {912,448,128,128};
const SDL_Rect RECT_ESSENCE_GRIS = {516,448,128,128};
const SDL_Rect RECT_ROUE_GRIS = {642,448,128,128};

const SDL_Rect RECT_ESSENCE = {0,448,128,128};
const SDL_Rect RECT_MOTEUR= {251,448,128,128};
const SDL_Rect RECT_HUILE = {384,448,128,128};
const SDL_Rect RECT_ROUE = {128,448,128,128};
const SDL_Rect RECT_BUS = {233,144,720,362};
/*
int SDL_Rect rect_Roue_Act = {0,0,0,0};
int SDL_Rect rect_Moteur_Act = {0,0,0,0};
int SDL_Rect rect_Essence_Act = {0,0,0,0};
int SDL_Rect rect_Huile_Act = {0,0,0,0};
*/
EcranQueteCampement::EcranQueteCampement(Controleur *controleur)
    : EcranGeneral (controleur),
      //m_spriteRoue{new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{64,128,128,128},SDL_Rect{0,448,128,128}}},
      m_spriteHuile{new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{890,300,128,128},
                    RECT_HUILE_GRIS}},
      //m_spriteEssence{new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{320+20,128,128,128},
                      //SDL_Rect{256,448,128,128}}},

      m_spriteMoteur{new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{779,300,128,128},
                    RECT_MOTEUR_GRIS}},
      m_tabEssence{new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{0,178,128,128},RECT_ESSENCE_GRIS},
                  new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{25,178+50,128,128},RECT_ESSENCE_GRIS},
                  new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{50,178+100,128,128},RECT_ESSENCE_GRIS},
                  new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{75,178+150,128,128},RECT_ESSENCE_GRIS}},
    m_tabRoue{new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{315+25,450-25,128,128},RECT_ROUE_GRIS},
                new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{695+25,450-25,128,128},RECT_ROUE_GRIS},
                new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{315,450,128,128},RECT_ROUE_GRIS},
                new Sprite{SPRITES_PRINCIPAUX,SDL_Rect{695,450,128,128},RECT_ROUE_GRIS}},
    m_bus{new Sprite(SPRITE_BUS,SDL_Rect{235,150,720,362},RECT_BUS )}
{
    coordBoutonCampement = {WIDTH_FENETRE_PRINCIPALE - 290, HEIGHT_FENETRE_PRINCIPALE - 100};
    const std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    SDL_Rect rectBoutonCampement = {
        static_cast<Sint16>(coordBoutonCampement.first), static_cast<Sint16>(coordBoutonCampement.second), static_cast<Uint16>(tailleB.first), static_cast<Uint16>(tailleB.second)};

    ajoutBoutonDansMapDeBoutons(new Bouton("Retour Campement",rectBoutonCampement,m_controleur, nullptr,true,
                                           POLICE_COLLEGED),&ActionsBoutons::boutonCampement);

   // m_fond = SDL_LoadBMP("../rsc/sprites/bus.bmp");
    m_fond = SDL_LoadBMP("../rsc/sprites/ecran_campement.bmp");
}

void EcranQueteCampement::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage){
    afficherFondEcran(fenetre_affichage);
    afficherBoutons(coord_souris, fenetre_affichage);
    //m_spriteRoue->afficher(fenetre_affichage);
    m_spriteMoteur->afficher(fenetre_affichage);
    for (int i = 0; i<4; i++)
       {
          m_tabEssence[i]->afficher(fenetre_affichage);
       }
    for (int i = 0; i<2; i++)
       {
          m_tabRoue[i]->afficher(fenetre_affichage);
       }
    m_spriteHuile->afficher(fenetre_affichage);
    m_bus->afficher(fenetre_affichage);
    for (int i = 2; i<4; i++)
       {
          m_tabRoue[i]->afficher(fenetre_affichage);
       }
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
    Campement * c = dynamic_cast<Campement*>(&obj);
    if (c != nullptr){
        // mise a jour de l'ecran
        std::vector<Objet *> objets = c->obtenirObjets();
        for(Objet* obj : objets){
            if(obj->obtenirType() == TypeObjet::Partie_bus){
                // truc a faire


            }
        }

    }

}
