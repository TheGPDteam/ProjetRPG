#include "ecrangeneral.h"


//!
//! \brief Constructeur écran général
//! \author pgutierrez
//! \date 23/11/16
//! \version 1.0
//!

EcranGeneral::EcranGeneral(Controleur *controleur) :
    DictionnaireDeBoutons(controleur),
    m_controleur{controleur}
{
    m_fond = SDL_LoadBMP("../rsc/sprites/ecran_titre.bmp");
}


//!
//! \brief Destructeur écran général
//! \author pgutierrez
//! \date 23/11/16
//! \version 1.0
//!

EcranGeneral::~EcranGeneral()
{
    SDL_FreeSurface(m_fond);
}

//!
//! \brief Destructeur écran général
//! \author rbourqui
//! \date 15/01/18
//! \version 1.0
//!
void EcranGeneral::afficherFondEcran(SDL_Surface* fenetre_affichage) {
    SDL_Rect fond_ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
    SDL_Rect dest_rect = {0, 0, 0, 0};
    SDL_BlitSurface(m_fond,&fond_ecran,fenetre_affichage,&dest_rect);
}
