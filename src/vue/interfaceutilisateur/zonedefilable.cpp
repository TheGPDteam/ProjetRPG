#include "zonedefilable.h"

#include "outilsvue.h"
#include "cliquable.h"
#include "chargementfeuilledesprite.h"
#include <SDL/SDL.h>
const int LARGEUR_BARRE_LATERALE = 10;


const SDL_Rect POSITION_BAS = initialiserRectangle(64, 256,64, 64);
const SDL_Rect POSITION_HAUT = initialiserRectangle(0, 256,64, 64);


ZoneDefilable::ZoneDefilable(Affichable * contenu, SDL_Color couleur, Controleur * controleur, bool actif, SDL_Rect rectangle)
    : Cliquable(controleur, actif), Affichable(rectangle), m_contenu{contenu}, m_couleur{couleur}/*,
      m_defilementBas(new Sprite(SPRITES_PRINCIPAUX, rectangle, POSITION_BAS)),
      m_defilementHaut(new Sprite(SPRITES_PRINCIPAUX, rectangle, POSITION_HAUT))*/

{
    m_fenetreGlissante = {0,0, m_rectangle.w, m_rectangle.h};
    SDL_Rect rect = m_contenu->rectangle();
    rect.x = rect.y = 0;
    if(m_rectangle.h < rect.h){
        rect.w -= LARGEUR_BARRE_LATERALE*1.2;
        m_fenetreGlissante.w -= LARGEUR_BARRE_LATERALE*1.2;
        m_contenu->redimensionner(rect);
    }
    m_contenu->changerRectangle(rect);

//    rect = initialiserRectangle(rectangle.x + rectangle.w - LARGEUR_BARRE_LATERALE, rectangle.y,
//                                         LARGEUR_BARRE_LATERALE, LARGEUR_BARRE_LATERALE);
//    m_defilementHaut->redimensionner(rect);
//    rect.y = rectangle.y + rectangle.h - LARGEUR_BARRE_LATERALE;
//    m_defilementBas->redimensionner(rect);
}


ZoneDefilable::~ZoneDefilable(){
    delete m_contenu;
//    delete m_defilementBas;
//    delete m_defilementHaut;
}

void ZoneDefilable::afficher(SDL_Surface *surface) {
    SDL_Rect rect = m_contenu->rectangle();
    if(m_fenetreGlissante.h >= rect.h)
        m_contenu->afficher(surface);
    else {
        SDL_Surface *horsEcran = SDL_CreateRGBSurface(SDL_HWSURFACE, rect.w, rect.h, 12,
                                                      0,0,0,0);
        SDL_Rect r = {0,0,rect.w, rect.h};

        SDL_FillRect(horsEcran, &r, SDL_MapRGB(surface->format, m_couleur.r, m_couleur.g, m_couleur.b));
        m_contenu->afficher(horsEcran);
        SDL_BlitSurface(horsEcran,
                        &m_fenetreGlissante,
                        surface,
                        &m_rectangle);

        SDL_FreeSurface(horsEcran);
        SDL_Rect pos = {m_rectangle.x+m_rectangle.w-LARGEUR_BARRE_LATERALE,  m_rectangle.y, LARGEUR_BARRE_LATERALE, m_rectangle.h};
        SDL_FillRect(surface, &pos, SDL_MapRGB(surface->format, 120, 120, 120));
//        m_defilementBas->afficher(surface);
//        m_defilementHaut->afficher(surface);
    }
}

void ZoneDefilable::redimensionner(SDL_Rect rectangle) {
    m_rectangle = rectangle;
    m_fenetreGlissante.x = 0;
    m_fenetreGlissante.w =  m_rectangle.w;
    m_fenetreGlissante.h = m_rectangle.h;
    int nouvelle_ordonnee =  std::min((int)m_fenetreGlissante.y, m_contenu->rectangle().h - m_fenetreGlissante.h);
    m_fenetreGlissante.y = nouvelle_ordonnee;
}

void ZoneDefilable::clique() {
    Cliquable * cliquable = dynamic_cast<Cliquable *>(m_contenu);
    if(cliquable != nullptr) cliquable->clique();
}


SDL_Rect ZoneDefilable::zone() const {
    return m_rectangle;
}

void ZoneDefilable::defiler(bool haut){
    if(m_fenetreGlissante.h < m_contenu->rectangle().h){
        // nouvelle ordonnée est bornée entre 0 et la hauteur du contenu moins la hauteur de la zone défilable
        int nouvelle_ordonnee = m_fenetreGlissante.y + (!haut ? 1. : -1.) * m_fenetreGlissante.h*VITESSE_DEFILEMENT ;
        nouvelle_ordonnee = std::max(0, nouvelle_ordonnee);
        nouvelle_ordonnee = std::min(nouvelle_ordonnee,m_contenu->rectangle().h - m_fenetreGlissante.h);

        m_fenetreGlissante.y = nouvelle_ordonnee;
    }
}
