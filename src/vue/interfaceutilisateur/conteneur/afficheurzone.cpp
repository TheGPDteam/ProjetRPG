#include "afficheurzone.h"
#include "utility"

AfficheurZone::AfficheurZone(){
    //* INITIALISATION DE L'AFFICHAGE DE LA CARTE *//
    for(int i = 0; i < DECALAGE_CARTE_X_SUPERIEUR; ++i)
        for(int j = 0; j < DECALAGE_CARTE_Y_SUPERIEUR; ++j)
            m_spritesCarte[i][j] = new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{static_cast<Sint16>(i*64), static_cast<Sint16>(j*64), 0, 0}, SDL_Rect{0, 0, 64, 64}};
}


AfficheurZone::~AfficheurZone(){
    for(auto colonne : m_spritesCarte)
        for(auto tuile : colonne)
            delete tuile;

    for(auto spriteObjet : m_spriteObjets)
        delete spriteObjet;
}


void AfficheurZone::mettreAJour(Carte* carte, Joueur * joueur, bool joueur_provoque_changement){
    m_spriteObjets.clear();

    //recupère la position du joueur sur la zone
    int posX = joueur->obtenirPosition().first - 5;
    int posY = joueur->obtenirPosition().second - 5;
    const Zone * zone = carte->obtenirZoneActive();

    // Debug aficher le nom de la map en cours
    //std::cout << m_carte->obtenirZoneActive()->obtenirNom() << std::endl;

    // Test si c'est un joueur
    if (joueur_provoque_changement){
        Tuile * tuile;
        // on deplace la zone autour du joueur pour qu'il reste au milieu
        for (int i = posX-DECALAGE_CARTE_X_INFERIEUR; i < posX + DECALAGE_CARTE_X_SUPERIEUR; ++i){
            for (int j = posY-DECALAGE_CARTE_Y_INFERIEUR; j < posY + DECALAGE_CARTE_Y_SUPERIEUR; ++j){

                // Ne pas rendre des tuiles ou des objets en dehors de la map
                if (i > 0 && i < zone->obtenirLargeur() && j > 0 && j < zone->obtenirHauteur()){

                    // On recupère le numéro de la tuile pour l'afficher
                    std::pair<int, int> temp(i,j);
                    tuile = zone->obtenirTuile(i,j);
                    // On cherche la bonne tuile sur l'atlas a partir de son numéro
                    SDL_Rect lecture = SDL_Rect{(tuile->obtenirNumero() % 16) * 64, (tuile->obtenirNumero() / 16) * 64, 64, 64};

                    (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);

                    // Affichage de la valise
                    if (zone->objetPresent(temp) && joueur->obtenirQuete()->obtenirType() == TypeQuete::QUETERECOLTE){
                        int x = i-posX-DECALAGE_CARTE_X_INFERIEUR;
                        int y = j-posY-DECALAGE_CARTE_Y_INFERIEUR;
                        m_spriteObjets.insert(new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{(short int)(x*64), (short int)(y*64), 128 , 64}, SDL_Rect{4 * 64, 13 * 64, 64, 64}});
                    }
                } else  {
                    // On met une tuile noire
                    SDL_Rect lecture = SDL_Rect{0, 0, 0, 0};

                    (m_spritesCarte[i-posX-DECALAGE_CARTE_X_INFERIEUR][j-posY-DECALAGE_CARTE_Y_INFERIEUR])->changementSprite(lecture);
                }
            }
        }

        //delete tuile;
    // Affichage des valises
    } else {
        for (int i = posX - DECALAGE_CARTE_X_INFERIEUR; i < posX + DECALAGE_CARTE_X_SUPERIEUR; ++i) {
            for (int j = posY - DECALAGE_CARTE_Y_INFERIEUR; j < posY + DECALAGE_CARTE_Y_SUPERIEUR; ++j) {
                if (j >= 0 && j <= 64 &&  i >= 0 && i <= 64) {
                    std::pair<int, int> temp(i, j);
                    if (zone->objetPresent(temp) && joueur->obtenirQuete()->obtenirType() == TypeQuete::QUETERECOLTE){
                        int x = i-posX-DECALAGE_CARTE_X_INFERIEUR;
                        int y = j-posY-DECALAGE_CARTE_Y_INFERIEUR;
                        m_spriteObjets.insert(new Sprite{SPRITES_PRINCIPAUX, SDL_Rect{(short int)(x*64), (short int)(y*64), 127, 64}, SDL_Rect{4 * 64, 13 * 64, 64, 64}});
                    }
                }
            }
        }
    }
}


void AfficheurZone::afficher(SDL_Surface *fenetre_affichage){
    for(auto c : m_spritesCarte)
        for(auto x : c)
            x->afficher(fenetre_affichage);

    for(auto spriteObjet : m_spriteObjets)
        spriteObjet->afficher(fenetre_affichage);
}
