#include "zonedefilable.h"


ZoneDefilable::ZoneDefilable(Affichable * contenu, Controleur * controleur, bool actif, SDL_Rect rectangle)
    :Cliquable(controleur, actif), Affichable(rectangle), m_contenu{contenu}
{
    m_fenetreGlissante = {0,0, m_rectangle.w, m_rectangle.h};
    SDL_Rect rect = m_contenu->rectangle();
    rect.x = rect.y = 0;
    m_contenu->changerRectangle(rect);
}

void ZoneDefilable::afficher(SDL_Surface *surface) {
    SDL_Rect rect = m_contenu->rectangle();
    if(m_fenetreGlissante.h >= rect.h)
        m_contenu->afficher(surface);
    else {
        SDL_Surface *horsEcran = SDL_CreateRGBSurface(SDL_SWSURFACE, rect.w, rect.h, 12,
                                                      0,0,0,0);
        m_contenu->afficher(horsEcran);
        SDL_BlitSurface(horsEcran,
                        &m_fenetreGlissante,
                        surface,
                        &m_rectangle);

        SDL_FreeSurface(horsEcran);
    }
}

void ZoneDefilable::redimensionner(SDL_Rect m_rectangle) {

}

void ZoneDefilable::clique() {

}


SDL_Rect ZoneDefilable::zone() const {
    return m_rectangle;
}

void ZoneDefilable::defiler(bool haut){
    if(m_fenetreGlissante.h < m_contenu->rectangle().h){
        // nouvelle ordonnée est bornée entre 0 et la hauteur du contenu moins la hauteur de la zone défilable
        int nouvelle_ordonnee = m_fenetreGlissante.y + (haut ? 1. : -1.) * m_fenetreGlissante.h*VITESSE_DEFILEMENT ;
        nouvelle_ordonnee = std::max(0, nouvelle_ordonnee);
        nouvelle_ordonnee = std::min(nouvelle_ordonnee,m_contenu->rectangle().h - m_fenetreGlissante.h);

        m_fenetreGlissante.y = nouvelle_ordonnee;
    }
}
