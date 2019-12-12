#include "afficheurzone.h"
#include "utility"

//! Constructeur de l'afficheur de zone
//!
//! \brief AfficheurZone::AfficheurZone
//!
AfficheurZone::AfficheurZone()
    : m_spriteJoueur{SpritePersonnage::obtenirSpritesPersonnage()}{
    //* INITIALISATION DE L'AFFICHAGE DE LA CARTE *//
    for(int i = 0; i < DECALAGE_CARTE_X_SUPERIEUR; ++i)
        for(int j = 0; j < DECALAGE_CARTE_Y_SUPERIEUR; ++j)
            m_spritesSol[i][j] = new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{static_cast<Sint16>(i*64), static_cast<Sint16>(j*64), 0, 0}, SDL_Rect{0, 0, 64, 64}};

    for(int i = 0; i < DECALAGE_CARTE_X_SUPERIEUR; ++i)
        for(int j = 0; j < DECALAGE_CARTE_Y_SUPERIEUR; ++j)
            m_spritesDecoration[i][j] = new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{static_cast<Sint16>(i*64), static_cast<Sint16>(j*64), 0, 0}, SDL_Rect{0, 0, 64, 64}};
}


//! Destructeur de l'afficheur de zone
//!
//! \brief AfficheurZone::~AfficheurZone
//!
AfficheurZone::~AfficheurZone(){
    for(auto colonne1 : m_spritesSol)
        for(auto tuile1 : colonne1)
            delete tuile1;

    for(auto colonne2 : m_spritesDecoration)
        for(auto tuile2 : colonne2)
            delete tuile2;

    for(auto spriteObjet : m_spriteObjets)
        delete spriteObjet;

    delete m_spriteJoueur;
}


//! \brief Met a jour le tableau contenant les tuiles, la position d'affichage du personnage, et de la position d'affichage des valises
//!
//! \param carte Carte contenant toutes les zones. On récupère
//! \param joueur
//! \param joueur_provoque_changement
//!
void AfficheurZone::mettreAJour(Carte* carte, Joueur * joueur){
    m_spriteObjets.clear();

    //recupère la position du joueur sur la zone
    int posX = joueur->obtenirPosition().first;
    int posY = joueur->obtenirPosition().second;
    const Zone * zone = carte->obtenirZoneActive();

    // Test si c'est un joueur
    Tuile * tuile;

    std::vector<int> decalage = calculerDecalageBord(posX, posY, zone->obtenirLargeur(), zone->obtenirHauteur());
    // Sprite du personnage aux nouvelles coordonnées
    m_spriteJoueur->changerPosition(decalage[0] * 64, decalage[1] * 64);

    for (int i = 0; i < LARGEUR; i++){
        for(int j = 0; j < HAUTEUR; j++){
            // On recupère le numéro de la tuile pour l'afficher
            std::pair<int, int> temp(i + posX - decalage[0], j + posY - decalage[1]);

            // Ne pas rendre des tuiles ou des objets en dehors de la map
            if (temp.first >= 0 && temp.first < zone->obtenirLargeur() && temp.second >= 0 && temp.second < zone->obtenirHauteur()){

                tuile = zone->obtenirTuile(temp.first, temp.second);
                // On cherche la bonne tuile sur l'atlas a partir de son numéro
                SDL_Rect lectureSol = SDL_Rect{(tuile->obtenirSol() % 16) * 64, (tuile->obtenirSol() / 16) * 64, 64, 64};
                (m_spritesSol[i][j])->changementSprite(lectureSol);

                if(tuile->estDecoree()){
                    SDL_Rect lectureDecoration = SDL_Rect{(tuile->obtenirDecoration() % 16) * 64, (tuile->obtenirDecoration() / 16) * 64, 64, 64};
                    (m_spritesDecoration[i][j])->changementSprite(lectureDecoration);
                }
                else {
                    SDL_Rect lecture2 = SDL_Rect{0, 0, 0, 0};
                    (m_spritesDecoration[i][j])->changementSprite(lecture2);
                }

                // Affichage de la valise
                if (zone->objetPresent(temp) && joueur->obtenirQuete()->obtenirType() == TypeQuete::QUETERECOLTE){
                    int x = i;
                    int y = j;
                    m_spriteObjets.insert(new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{(short int)(x*64), (short int)(y*64), 128 , 64}, SDL_Rect{4 * 64, 13 * 64, 64, 64}});
                }
            } else  {
                // On met une tuile noire
                SDL_Rect lecture1 = SDL_Rect{0, 0, 0, 0};
                (m_spritesSol[i][j])->changementSprite(lecture1);

                SDL_Rect lecture2 = SDL_Rect{0, 0, 0, 0};
                (m_spritesDecoration[i][j])->changementSprite(lecture2);
            }
        }
    }
}


//!
//! \brief Calcule le decalage en fonction du la positon du personnage
//!        Le décalage sera utilsé pour choisir la position d'affichage de la map et la position d'affichage du personnage
//!
//! @param positionX Position x du personnage
//! @param positionY Position y du personnage
//! @param largeur_zone Largeur de la zone
//! @param hauteur_zone Hauteur de la zone
//! \version 0.1
//!
//! Calcule le decalage variant de 0 à LARGEUR ou HAUTEUR
//!
std::vector<int> AfficheurZone::calculerDecalageBord(int positionX, int positionY, int largeur_zone, int hauteur_zone){
    std::vector<int> decalage;
    int moitieEcranLargeur = (LARGEUR-1)/2;
    int moitieEcranHauteur = (HAUTEUR-1)/2;

    decalage.push_back(moitieEcranLargeur);
    decalage.push_back(moitieEcranHauteur);

    // Decalage si le personnage va vers le bord gauche de la zone
    if (positionX <= moitieEcranLargeur){
        decalage[0] = positionX;

    // Decalage si le personnage va vers le bord droite de la zone
    } else if (positionX >= largeur_zone - moitieEcranLargeur){
        decalage[0] = LARGEUR - largeur_zone + positionX;
    }

    // Decalage si le personnage va vers le bord haut de la zone
    if(positionY <= moitieEcranHauteur){
        decalage[1] = positionY;

    // Decalage si le personnage va vers le bord bas de la zone
    } else if (positionY >= hauteur_zone - moitieEcranHauteur){
        decalage[1] = HAUTEUR - hauteur_zone + positionY;
    }

    return decalage;
}


//! Afficher le tableau des tuiles, le personnage et les objets sur l'écran
//!
//! \brief AfficheurZone::afficher
//! \param fenetre_affichage
//!
void AfficheurZone::afficher(SDL_Surface *fenetre_affichage){
    for(auto c1 : m_spritesSol)
        for(auto x1 : c1)
            x1->afficher(fenetre_affichage);

    for(auto c2 : m_spritesDecoration)
        for(auto x2 : c2)
            x2->afficher(fenetre_affichage);

    for(auto spriteObjet : m_spriteObjets)
        spriteObjet->afficher(fenetre_affichage);

    m_spriteJoueur->afficher(fenetre_affichage);
}


//! Obtenir le sprite du personnage
//!
//! \brief AfficheurZone::obtenirSpritePersonnage
//! \return
//!
SpritePersonnage* AfficheurZone::obtenirSpritePersonnage(){
    return m_spriteJoueur;
}
